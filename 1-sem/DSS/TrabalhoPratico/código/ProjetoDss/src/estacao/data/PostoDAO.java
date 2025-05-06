package estacao.data;

import estacao.business.posto.Posto;

import java.sql.*;
import java.util.*;
import java.util.stream.Collectors;

public class PostoDAO {
    public static PostoDAO singleton = null;

    private PostoDAO() {
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            String sql = "CREATE TABLE IF NOT EXISTS postos (" +
                    "IdPosto int NOT NULL PRIMARY KEY," +
                    "IdMec int NOT NULL," +
                    "foreign key(IdMec) references mecanicos(Id))";
            stm.executeUpdate(sql);

            sql = "CREATE TABLE IF NOT EXISTS servicosprestados (" +
                    "IdPosto int NOT NULL," +
                    "IdServico int NOT NULL," +
                    "PRIMARY KEY (IdPosto, IdServico)," +
                    "foreign key(IdPosto) references postos(IdPosto)," +
                    "foreign key(IdServico) references servicos(IdServico))";
            stm.executeUpdate(sql);

            sql = "CREATE TABLE IF NOT EXISTS tarefas (" +
                    "IdPosto int NOT NULL," +
                    "IdServico int NOT NULL," +
                    "Matricula varchar(6) NOT NULL," +
                    "PRIMARY KEY (IdPosto,IdServico,Matricula)," +
                    "foreign key(IdPosto) references postos(IdPosto)," +
                    "foreign key(IdServico) references servicos(IdServico)," +
                    "foreign key(Matricula) references veiculos(Matricula))";
            stm.executeUpdate(sql);

        } catch (SQLException e) {
            // Error creating table
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
    }
    public static PostoDAO getInstance() {
        if (PostoDAO.singleton == null) {
            PostoDAO.singleton = new PostoDAO();
        }
        return PostoDAO.singleton;
    }

    public Posto getPosto(int idPosto){
        Posto p = null;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT * FROM postos WHERE IdPosto ='"+idPosto+"'")) {
            if (rs.next()) {
                p = new Posto(rs.getInt("IdPosto"), rs.getInt("IdMec"));

                Map<String, List<Integer>> tarefas = new HashMap<>();
                try (ResultSet rsTarefas = stm.executeQuery("SELECT Matricula, IdServico FROM tarefas WHERE IdPosto ='"+idPosto+"'")) {
                    while (rsTarefas.next()) {
                        String matricula = rsTarefas.getString("Matricula");
                        int idServico = rsTarefas.getInt("IdServico");

                        tarefas.computeIfAbsent(matricula, k -> new ArrayList<>()).add(idServico);
                    }
                }
                p.setTarefas(tarefas);

                List<Integer> servicosPrestados = new ArrayList<>();
                try (ResultSet rsServicos = stm.executeQuery("SELECT IdServico FROM servicosprestados WHERE IdPosto ='"+idPosto+"'")) {
                    while (rsServicos.next()) {
                        int idServico = rsServicos.getInt("IdServico");
                        servicosPrestados.add(idServico);
                    }
                }
                p.setServicosPrestados(servicosPrestados);
            }
        } catch (SQLException e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return p;
    }
    public List<Posto> getPostos() {
        List<Posto> postosList = new ArrayList<>();
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT p.IdPosto, p.IdMec, t.Matricula AS TarefaMatricula, t.IdServico AS TarefaIdServico, GROUP_CONCAT(s.IdServico) AS ServicoPrestadoIds " +
                     "FROM postos p " +
                     "LEFT JOIN tarefas t ON p.IdPosto = t.IdPosto " +
                     "LEFT JOIN servicosprestados s ON p.IdPosto = s.IdPosto " +
                     "GROUP BY p.IdPosto, t.Matricula, t.IdServico")) {

            Map<Integer, Posto> postoMap = new HashMap<>();

            while (rs.next()) {
                int idPosto = rs.getInt("IdPosto");

                if (!postoMap.containsKey(idPosto)) {
                    Posto posto = new Posto(idPosto, rs.getInt("IdMec"));
                    postosList.add(posto);
                    postoMap.put(idPosto, posto);
                }

                Posto currentPosto = postoMap.get(idPosto);

                String matricula = rs.getString("TarefaMatricula");
                if (matricula != null) {
                    int tarefaIdServico = rs.getInt("TarefaIdServico");
                    currentPosto.getTarefas2().computeIfAbsent(matricula, k -> new ArrayList<>()).add(tarefaIdServico);
                }

                String servicoPrestadoIds = rs.getString("ServicoPrestadoIds");
                if (servicoPrestadoIds != null) {
                    List<Integer> servicosPrestados = Arrays.stream(servicoPrestadoIds.split(","))
                            .map(Integer::parseInt)
                            .collect(Collectors.toList());
                    currentPosto.setServicosPrestados(servicosPrestados);
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return postosList;
    }




    public void updatePosto(Posto posto) {
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             PreparedStatement pstmtTarefas = conn.prepareStatement("INSERT INTO tarefas (IdPosto, IdServico, Matricula) VALUES (?, ?, ?)");
             PreparedStatement pstmtServicos = conn.prepareStatement("INSERT INTO servicosprestados (IdPosto, IdServico) VALUES (?, ?)")) {

            conn.setAutoCommit(false);

            // Delete existing entries for the Posto in the tarefas and servicosprestados tables
            try (PreparedStatement deleteTarefas = conn.prepareStatement("DELETE FROM tarefas WHERE IdPosto = ?");
                 PreparedStatement deleteServicos = conn.prepareStatement("DELETE FROM servicosprestados WHERE IdPosto = ?")) {
                deleteTarefas.setInt(1, posto.getIdPosto());
                deleteTarefas.executeUpdate();

                deleteServicos.setInt(1, posto.getIdPosto());
                deleteServicos.executeUpdate();
            }

            // Insert updated tarefas for the Posto
            for (Map.Entry<String, List<Integer>> entry : posto.getTarefas2().entrySet()) {
                String matricula = entry.getKey();
                for (Integer idServico : entry.getValue()) {
                    pstmtTarefas.setInt(1, posto.getIdPosto());
                    pstmtTarefas.setInt(2, idServico);
                    pstmtTarefas.setString(3, matricula);
                    pstmtTarefas.addBatch();
                }
            }

            // Insert updated servicosprestados for the Posto
            for (Integer idServico : posto.getServicosPrestados()) {
                pstmtServicos.setInt(1, posto.getIdPosto());
                pstmtServicos.setInt(2, idServico);
                pstmtServicos.addBatch();
            }

            // Execute batch updates
            pstmtTarefas.executeBatch();
            pstmtServicos.executeBatch();

            conn.commit();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
    }

}
