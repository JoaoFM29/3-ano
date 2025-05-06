package estacao.data;

import estacao.business.mecanico.Mecanico;

import java.sql.*;

public class MecanicoDAO {

    private static MecanicoDAO singleton = null;

    private MecanicoDAO() {
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            String sql = "CREATE TABLE IF NOT EXISTS mecanicos (" +
                    "Id int NOT NULL PRIMARY KEY," +
                    "Nome varchar(100) DEFAULT 0)";
            stm.executeUpdate(sql);
        } catch (SQLException e) {
            // Erro a criar tabela...
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
    }
    public static MecanicoDAO getInstance() {
        if (MecanicoDAO.singleton == null) {
            MecanicoDAO.singleton = new MecanicoDAO();
        }
        return MecanicoDAO.singleton;
    }

    public Mecanico getMecanico(int idMec){
        Mecanico m = null;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("select * from mecanicos where Id ='"+idMec+"'")) {
            if (rs.next()) {  // A chave existe na tabela
                m = new Mecanico(rs.getString("Nome"),rs.getInt("Id"));
            }
        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return m;
    }
}
