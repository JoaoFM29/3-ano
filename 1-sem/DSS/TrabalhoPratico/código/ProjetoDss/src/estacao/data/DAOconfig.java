package estacao.data;

public class DAOconfig {
    static final String USERNAME = "root";                       // Actualizar
    static final String PASSWORD = "nunonuno153";                       // Actualizar
    private static final String DATABASE = "estacao";          // Actualizar
    //private static final String DRIVER = "jdbc:mariadb";        // Usar para MariaDB
    private static final String DRIVER = "jdbc:mysql";        // Usar para MySQL
    static final String URL = DRIVER+"://localhost:3306/"+DATABASE;
}
