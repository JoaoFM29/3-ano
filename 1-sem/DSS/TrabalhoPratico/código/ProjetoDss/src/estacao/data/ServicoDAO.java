package estacao.data;


import estacao.business.posto.*;

import java.sql.*;
import java.util.*;

public class ServicoDAO {

    private static ServicoDAO singleton = null;

    private ServicoDAO() {
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {

            String sql = "CREATE TABLE IF NOT EXISTS servicos (" +
                    "IdServico int NOT NULL PRIMARY KEY," +
                    "Duracao float NOT NULL," +
                    "Designacao varchar(100) NOT NULL," +
                    "Tipo varchar(4) NOT NULL," +
                    "Preco float DEFAULT 0)";
            stm.executeUpdate(sql);

            sql = "CREATE TABLE IF NOT EXISTS packs (" +
                    "IdPack int NOT NULL PRIMARY KEY," +
                    "Nome varchar(100) DEFAULT 0)";
            stm.executeUpdate(sql);

            sql = "CREATE TABLE IF NOT EXISTS PackServico (" +
                    "IdPack int NOT NULL," +
                    "IdServico int NOT NULL," +
                    "PRIMARY KEY (IdPack, IdServico)," +
                    "FOREIGN KEY (IdServico) REFERENCES servicos(IdServico)," +
                    "FOREIGN KEY (IdPack) REFERENCES packs(IdPack))";
            stm.executeUpdate(sql);

            sql = "CREATE TABLE IF NOT EXISTS veiculoservico (" +
                    "Matricula varchar(6) NOT NULL," +
                    "IdServico int NOT NULL," +
                    "PRIMARY KEY (Matricula, IdServico)," +
                    "FOREIGN KEY (IdServico) REFERENCES servicos(IdServico)," +
                    "FOREIGN KEY (Matricula) REFERENCES veiculos(Matricula))";
            stm.executeUpdate(sql);

        } catch (SQLException e) {
            // Error creating table
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
    }
    public static ServicoDAO getInstance() {
        if (ServicoDAO.singleton == null) {
            ServicoDAO.singleton = new ServicoDAO();
        }
        return ServicoDAO.singleton;
    }

    public Servico getServico(int idServico) {
        Servico s = null;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT * FROM servicos WHERE IdServico='"+idServico+"'")) {
            if (rs.next()) {  // A chave existe na tabela
                // Reconstruir a colecção de alunos da turma
                String tipo = rs.getString("Tipo");
                switch (tipo) {
                    case "gaso":
                    s = new ServicoGasoleo(rs.getInt("IdServico"),rs.getString("Designacao"),
                                rs.getFloat("Duracao"), rs.getFloat("Preco"));
                        break;
                    case "gasa":
                        s = new ServicoGasolina(rs.getInt("IdServico"),rs.getString("Designacao"),
                                rs.getFloat("Duracao"), rs.getFloat("Preco"));
                        break;
                    case "comb":
                        s = new ServicoCombustao(rs.getInt("IdServico"),rs.getString("Designacao"),
                                rs.getFloat("Duracao"), rs.getFloat("Preco"));
                        break;
                    case "univ":
                        s = new ServicoUniversal(rs.getInt("IdServico"),rs.getString("Designacao"),
                                rs.getFloat("Duracao"), rs.getFloat("Preco"));
                        break;
                    case "elec":
                        s = new ServicoEletrico(rs.getInt("IdServico"),rs.getString("Designacao"),
                                rs.getFloat("Duracao"), rs.getFloat("Preco"));
                        break;
                    default:
                        s = new Checkup(rs.getInt("IdServico"),rs.getString("Designacao"),
                                rs.getFloat("Duracao"), rs.getFloat("Preco"));

                        break;
                }
            }
        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return s;
    }

    public boolean isPack(int idServico){
        Servico se = null;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT * FROM servicos WHERE IdServico='"+idServico+"'")) {
            if (rs.next()) {  // A chave existe na tabela
                // Reconstruir a colecção de alunos da turma
                String tipo = rs.getString("Tipo");
                switch (tipo) {
                    case "gaso":
                        se = new ServicoGasoleo(rs.getInt("IdServico"),rs.getString("Designacao"),
                                rs.getFloat("Duracao"), rs.getFloat("Preco"));
                        break;
                    case "gasa":
                        se = new ServicoGasolina(rs.getInt("IdServico"),rs.getString("Designacao"),
                                rs.getFloat("Duracao"), rs.getFloat("Preco"));
                        break;
                    case "comb":
                        se = new ServicoCombustao(rs.getInt("IdServico"),rs.getString("Designacao"),
                                rs.getFloat("Duracao"), rs.getFloat("Preco"));
                        break;
                    case "univ":
                        se = new ServicoUniversal(rs.getInt("IdServico"),rs.getString("Designacao"),
                                rs.getFloat("Duracao"), rs.getFloat("Preco"));
                        break;
                    case "elec":
                        se = new ServicoEletrico(rs.getInt("IdServico"),rs.getString("Designacao"),
                                rs.getFloat("Duracao"), rs.getFloat("Preco"));
                        break;
                    default:
                        se = new Checkup(rs.getInt("IdServico"),rs.getString("Designacao"),
                                rs.getFloat("Duracao"), rs.getFloat("Preco"));

                        break;
                }
            }
        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        boolean b = (se == null);
        return b;
    }
    public Map<String, List<Servico>> getTarefas(int idPosto) {
        Map<String, List<Servico>> ms = new HashMap<>();
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT tarefas.IdPosto, tarefas.Matricula, servicos.* FROM tarefas " +
                     " INNER JOIN servicos ON tarefas.IdServico = servicos.IdServico " +
                     " WHERE tarefas.IdPosto='" + idPosto + "'")) {

            while (rs.next()) {
                String matricula = rs.getString("tarefas.Matricula");
                int idServico = rs.getInt("servicos.IdServico");
                String tipo = rs.getString("servicos.Tipo"); // Assuming this column exists in the servicos table
                Servico s;

                switch (tipo) {
                    case "gaso":
                        s = new ServicoGasoleo(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    case "gasa":
                        s = new ServicoGasolina(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    case "comb":
                        s = new ServicoCombustao(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    case "univ":
                        s = new ServicoUniversal(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    case "elec":
                        s = new ServicoEletrico(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    default:
                        s = new Checkup(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                }


                if (ms.containsKey(matricula)) {

                    ms.get(matricula).add(s);
                } else {

                    List<Servico> servicoList = new ArrayList<>();
                    servicoList.add(s);
                    ms.put(matricula, servicoList);
                }
            }
        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return ms;
    }

    public List<Servico> getServicosPrestados(int idPosto) {
        List<Servico> servicosPrestados = new ArrayList<>();
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT servicosprestados.IdPosto, servicos.* FROM servicosprestados " +
                     " INNER JOIN servicos ON servicosprestados.IdServico = servicos.IdServico " +
                     " WHERE servicosprestados.IdPosto='" + idPosto + "'")) {

            while (rs.next()) {
                int idServico = rs.getInt("servicos.IdServico");
                String tipo = rs.getString("servicos.Tipo"); // Assuming this column exists in the servicos table
                Servico s;

                switch (tipo) {
                    case "gaso":
                        s = new ServicoGasoleo(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    case "gasa":
                        s = new ServicoGasolina(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    case "comb":
                        s = new ServicoCombustao(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    case "univ":
                        s = new ServicoUniversal(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    case "elec":
                        s = new ServicoEletrico(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    default:
                        s = new Checkup(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                }

                servicosPrestados.add(s);
            }
        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return servicosPrestados;
    }

    public PackServico getPack(int idPack) {
        PackServico p = null;
        List<Servico> servicosDoPack = new ArrayList<>();

        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT * FROM PackServico " +
                     " INNER JOIN servicos ON PackServico.IdServico = servicos.IdServico " +
                     " INNER JOIN packs ON PackServico.IdPack = packs.IdPack" +
                     " WHERE PackServico.IdPack='" + idPack + "'")) {

            while (rs.next()) {
                if (p == null) {
                    int packId = rs.getInt("IdPack");
                    p = new PackServico(packId,rs.getString("Nome"),null);
                }

                int idServico = rs.getInt("servicos.IdServico");
                String tipo = rs.getString("servicos.Tipo");
                Servico s;

                switch (tipo) {
                    case "gaso":
                        s = new ServicoGasoleo(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    case "gasa":
                        s = new ServicoGasolina(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    case "comb":
                        s = new ServicoCombustao(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    case "univ":
                        s = new ServicoUniversal(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    case "elec":
                        s = new ServicoEletrico(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    default:
                        s = new Checkup(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                }

                servicosDoPack.add(s);
            }

            // Set the list of Servicos to the PackServico object
            if (p != null) {
                p.setServicos(servicosDoPack);
            }

        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }

        return p;
    }

    public List<Servico> getFicha(String mat){
        List<Servico> ficha = new ArrayList<>();
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("select * from veiculoservico" +
                     " INNER JOIN servicos ON veiculoservico.IdServico = servicos.IdServico" +
                     " WHERE  Matricula='" + mat + "'")) {

            while (rs.next()) {
                int idServico = rs.getInt("servicos.IdServico");
                String tipo = rs.getString("servicos.Tipo"); // Assuming this column exists in the servicos table
                Servico s;

                switch (tipo) {
                    case "gaso":
                        s = new ServicoGasoleo(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    case "gasa":
                        s = new ServicoGasolina(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    case "comb":
                        s = new ServicoCombustao(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    case "univ":
                        s = new ServicoUniversal(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    case "elec":
                        s = new ServicoEletrico(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                    default:
                        s = new Checkup(idServico, rs.getString("servicos.Designacao"), rs.getFloat("servicos.Duracao"), rs.getFloat("servicos.Preco"));
                        break;
                }

                ficha.add(s);
            }
        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return ficha;
    }
}
