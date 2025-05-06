SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='ONLY_FULL_GROUP_BY,STRICT_TRANS_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_ENGINE_SUBSTITUTION';

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
DROP SCHEMA IF EXISTS `estacao` ;

-- -----------------------------------------------------
-- Schema mydb
-- -----------------------------------------------------
CREATE SCHEMA IF NOT EXISTS `estacao` DEFAULT CHARACTER SET utf8 ;
USE `estacao` ;


select tarefas.IdPosto,tarefas.Matricula,servicos.* from tarefas
    INNER JOIN servicos ON tarefas.IdServico = servicos.IdServico
    WHERE tarefas.IdPosto=1;

select servicosprestados.IdPosto,servicos.* from servicosprestados
    INNER JOIN servicos ON servicosprestados.IdServico = servicos.IdServico
    WHERE servicosprestados.IdPosto=1;

select * from PackServico
    INNER JOIN servicos ON PackServico.IdServico = servicos.IdServico
    WHERE  PackServico.IdPack=3;


select * from veiculoservico
    INNER JOIN servicos ON veiculoservico.IdServico = servicos.IdServico
    WHERE  Matricula='AB01CK';


SELECT * FROM clientes WHERE Nif = 1;

select m.Tipo,m.Modelo FROM veiculos
INNER  JOIN veiculosmotores v on veiculos.Matricula = v.Matricula
INNER JOIN motores m on v.Modelo = m.Modelo
WHERE  v.Matricula = 1;

select * From veiculoservico
    where Matricula = 1;

select * from mecanicos where Id = 1;

select * from postos where IdPosto = 1;


/*Mecanico*/
INSERT INTO mecanicos(Id,Nome) Values(1,'Arlindo');
INSERT INTO mecanicos(Id,Nome) Values(2,'Joao');
INSERT INTO mecanicos(Id,Nome) Values(3,'Miguel');
INSERT INTO mecanicos(Id,Nome) Values(4,'Igor');

/*Cliente e carro*/
INSERT INTO clientes(Nif,Contacto,Email,Morada,Nome) VALUES (1,927485427,'aksjd@gmail.com','Vila franca','Figueira');
INSERT INTO clientes(Nif,Contacto,Email,Morada,Nome) VALUES (2,927485428,'ummail@gmail.com','Ponte lima','Roberto');
INSERT INTO veiculos(Matricula,Caracteristicas,IdCliente) VALUES ('OX92KJ','Muito muito rapido',1);
INSERT INTO veiculos(Matricula,Caracteristicas,IdCliente) VALUES ('GG77GG','E Hibrido',2);
INSERT INTO motores(Modelo, Tipo) VALUES ('Ganda Motor gasolina','ga');
INSERT INTO motores(Modelo, Tipo) VALUES ('Ganda Motor gasoleo','go');
INSERT INTO motores(Modelo, Tipo) VALUES ('Ganda Motor eletrico','el');
INSERT INTO veiculosmotores(Modelo, Matricula) VALUES ('Ganda Motor gasolina','OX92KJ');
INSERT INTO veiculosmotores(Modelo, Matricula) VALUES ('Ganda Motor gasoleo','GG77GG');
INSERT INTO veiculosmotores(Modelo, Matricula) VALUES ('Ganda Motor eletrico','GG77GG');

/*Servico*/
insert into servicos value(0,20,'CheckUp','chec',10);
insert into servicos value(1,20,'Trocar Peneus','univ',10);
insert into servicos value(2,10,'Mudar oleo','gasa',20);
insert into servicos value(6,10,'Mudar velas','gasa',20);
insert into servicos value(4,20,'Mudar farois','univ',10);
insert into servicos value(5,10,'Limpar piscas','univ',12);
insert into servicos value(7,30,'Mudar Bateria','elec',20);

insert into packs value(3,'Mudar luzes');
insert into PackServico value(3,4);
insert into PackServico value(3,5);

/*Posto*/
insert into postos value (1,1);
insert into postos value (2,2);
insert into postos value (3,3);
insert into postos value (4,4);
insert into servicosprestados value (1,1);
insert into servicosprestados value (1,4);
insert into servicosprestados value (1,5);
insert into servicosprestados value (2,0);
insert into servicosprestados value (3,2);
insert into servicosprestados value (3,6);
insert into servicosprestados value (4,7);


select * from postos
INNER join tarefas t on postos.IdPosto = t.IdPosto
INNER join servicosprestados s on postos.IdPosto = s.IdPosto;

SELECT p.*, t.Matricula, t.IdServico, s.IdServico FROM postos p
                     LEFT JOIN tarefas t ON p.IdPosto = t.IdPosto
                     LEFT JOIN servicosprestados s ON p.IdPosto = s.IdPosto;

SELECT
    p.IdPosto,
    p.IdMec,
    t.Matricula AS TarefaMatricula,
    t.IdServico AS TarefaIdServico,
    GROUP_CONCAT(s.IdServico) AS ServicoPrestadoIds
FROM
    postos p
LEFT JOIN
    tarefas t ON p.IdPosto = t.IdPosto
LEFT JOIN
    servicosprestados s ON p.IdPosto = s.IdPosto
GROUP BY
    p.IdPosto, t.Matricula, t.IdServico



