package estacao.data;

import estacao.business.posto.*;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class ClienteDAO {


    private static ClienteDAO singleton = null;

    private ClienteDAO() {
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            String sql = "CREATE TABLE IF NOT EXISTS clientes (" +
                    "Nif int NOT NULL PRIMARY KEY," +
                    "Contacto int NOT NULL," +
                    "Email varchar(100) NOT NULL," +
                    "Morada varchar(100) NOT NULL," +
                    "Nome varchar(100) DEFAULT '0')";
            stm.executeUpdate(sql);

            sql = "CREATE TABLE IF NOT EXISTS veiculos (" +
                    "Matricula varchar(6) NOT NULL PRIMARY KEY," +
                    "Caracteristicas varchar(300) NOT NULL," +
                    "IdCliente int NOT NULL," +
                    "foreign key(IdCliente) references clientes(Nif))";
            stm.executeUpdate(sql);

            sql = "CREATE TABLE IF NOT EXISTS vouchers (" +
                    "Valor float NOT NULL," +
                    "IdCliente int NOT NULL," +
                    "foreign key(IdCliente) references clientes(Nif)," +
                    "primary key(Valor, IdCliente))";
            stm.executeUpdate(sql);

            sql = "CREATE TABLE IF NOT EXISTS motores (" +
                    "Modelo varchar(100) NOT NULL PRIMARY KEY," +
                    "Tipo varchar(2) DEFAULT '0')";
            stm.executeUpdate(sql);

            sql = "CREATE TABLE IF NOT EXISTS veiculosmotores (" +
                    "Modelo varchar(100) NOT NULL," +
                    "Matricula varchar(6) NOT NULL," +
                    "foreign key(Modelo) references motores(Modelo)," +
                    "foreign key(Matricula) references veiculos(Matricula)," +
                    "primary key(Modelo, Matricula))";
            stm.executeUpdate(sql);

        } catch (SQLException e) {
            // Error creating table
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
    }
    public static ClienteDAO getInstance() {
        if (ClienteDAO.singleton == null) {
            ClienteDAO.singleton = new ClienteDAO();
        }
        return ClienteDAO.singleton;
    }

    public Cliente getCliente(int Nif){
        Cliente c = null;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT * FROM clientes WHERE Nif='"+Nif+"'")) {
            if (rs.next()) {  // A chave existe na tabela
                c = new Cliente(rs.getString("Nome"),rs.getInt("Contacto"),
                        rs.getString("Email"),rs.getInt("Nif"),rs.getString("Morada"));

                List<Veiculo> lv = new ArrayList<>();

                try(ResultSet rsb = stm.executeQuery("select * FROM veiculos" +
                        " INNER  JOIN veiculosmotores v on veiculos.Matricula = v.Matricula" +
                        " INNER JOIN motores m on v.Modelo = m.Modelo\n" +
                        " WHERE  IdCliente ='"+Nif+"'")){
                    while (rsb.next()){

                        String mat = rsb.getString("Matricula");
                        Veiculo v = new Veiculo(mat,rsb.getString("Caracteristicas"),null,null);

                        List<Motor> lm = new ArrayList<>();

                        try(ResultSet rsa = stm.executeQuery("select m.Tipo,m.Modelo FROM veiculos" +
                                " INNER  JOIN veiculosmotores v on veiculos.Matricula = v.Matricula" +
                                " INNER JOIN motores m on v.Modelo = m.Modelo" +
                                " WHERE  v.Matricula ='"+mat+"'")){
                            while (rsa.next()){
                                String tipo = rsa.getString("Tipo");
                                Motor m;
                                switch (tipo) {
                                    case "el":
                                        m = new MotorEletrico(rsa.getString("Modelo"));
                                        break;
                                    case "ga":
                                        m = new MotorGasolina(rsa.getString("Modelo"));
                                        break;
                                    default:
                                        m = new MotorGasoleo(rsa.getString("Modelo"));
                                        break;
                                }
                                lm.add(m);
                            }
                        }

                        v.setMotor(lm);

                        List<Integer> f = new ArrayList<>();
                        try(ResultSet rsc = stm.executeQuery("select * From veiculoservico" +
                                "    where Matricula ='"+mat+"'")){
                            while (rsc.next()){
                                f.add(rsc.getInt("IdServico"));
                            }
                        }
                        v.setFichaVeiculo(f);
                        lv.add(v);
                    }

                }
                for(Veiculo vtemp :lv)
                    c.addVeiculo(vtemp);


            }
        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return c;
    }

    public void updateCliente(Cliente c) {
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD)) {
            // Update Cliente information
            String updateClienteQuery = "UPDATE clientes SET Nome=?, Contacto=?, Email=?, Morada=? WHERE Nif=?";
            try (PreparedStatement updateClienteStmt = conn.prepareStatement(updateClienteQuery)) {
                updateClienteStmt.setString(1, c.getNome());
                updateClienteStmt.setInt(2, c.getContacto());
                updateClienteStmt.setString(3, c.getEmail());
                updateClienteStmt.setString(4, c.getMorada());
                updateClienteStmt.setInt(5, c.getNif());
                updateClienteStmt.executeUpdate();
            }

            // Clear existing associations with Veiculos
            String deleteVeiculoServicoQuery = "DELETE FROM veiculoservico WHERE Matricula=?";
            List<Veiculo> veiculos = c.getVeiculos();
            for (Veiculo v : veiculos) {
                try (PreparedStatement deleteVeiculoServicoStmt = conn.prepareStatement(deleteVeiculoServicoQuery)) {
                    deleteVeiculoServicoStmt.setString(1, v.getMatricula());
                    deleteVeiculoServicoStmt.executeUpdate();
                }

                // Update Veiculo information
                String updateVeiculoQuery = "UPDATE veiculos SET Caracteristicas=? WHERE Matricula=?";
                try (PreparedStatement updateVeiculoStmt = conn.prepareStatement(updateVeiculoQuery)) {
                    updateVeiculoStmt.setString(1, v.getCaracterizacao());
                    updateVeiculoStmt.setString(2, v.getMatricula());
                    updateVeiculoStmt.executeUpdate();
                }

                // Add updated services related to Veiculo
                List<Integer> servicos = v.getFichaVeiculo();
                String insertServicoQuery = "INSERT INTO veiculoservico(Matricula, IdServico) VALUES (?, ?)";
                for (Integer servico : servicos) {
                    try (PreparedStatement insertServicoStmt = conn.prepareStatement(insertServicoQuery)) {
                        insertServicoStmt.setString(1, v.getMatricula());
                        insertServicoStmt.setInt(2, servico);
                        insertServicoStmt.executeUpdate();
                    }
                }
            }
        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
    }


}
