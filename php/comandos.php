<?php

# Conexão com o bando de dados MySQL ***********************************************
$servidor = "localhost";
$usuario = "root";
$senha = "";
$database = "evento_php";

$conexao = mysqli_connect($servidor, $usuario, $senha, $database)
	or die("Erro ao conectar"); #taskkill/PID 5782 /F

/*
# Craindo tabelas usando PHP ********************************************************
# Tabela participantes (nome do participante, CPF, email)
$query = "CREATE TABLE PARTICIPANTES(
	id_participante int not null auto_increment,
	nome_participante varchar(255) not null,
	cpf varchar(11) not null,
	email varchar(255) not null,
	primary key(id_participante)
)";

if($executar = mysqli_query($conexao, $query))
	echo "Executou com sucesso! (participantes)<br>";
else echo "Falha ao executar (participantes)<br>";

# Tabela atividades (nome do atividade, carga horaria)
$query = "CREATE TABLE ATIVIDADES(
	id_atividade int not null auto_increment,
	nome_atividade varchar(255) not null,
	carga_horaria int not null,
	primary key(id_atividade)
)";

if($executar = mysqli_query($conexao, $query))
	echo "Executou com sucesso! (atividades)<br>";
else echo "Falha ao executar (atividades)<br>";


# Tabela participante_atividade (participante, atividade)
$query = "CREATE TABLE PARTICIPANTE_ATIVIDADE(
	id_participante_atividade int not null auto_increment,
	id_participante int not null,
	id_atividade int not null,
	primary key(id_participante_atividade)
)";

if($executar = mysqli_query($conexao, $query))
	echo "Executou com sucesso! (participante_atividade)<br>";
else echo "Falha ao executar (participante_atividade)<br>";

# Inserindo dados nas tabelas usando PHP **********************************************
$query = "INSERT INTO PARTICIPANTES(nome_participante, cpf, email)
	VALUES('Gabriel Vicente Rosa', '13597327648', 'gabrielvrosa@gmail.com')";
if($executar = mysqli_query($conexao, $query))
	echo "Executou com sucesso! (inserção participante)<br>";
else echo "Falha ao executar (inserção participante)<br>";

# Inserir atividade
#$query = "INSERT INTO ATIVIDADES(nome_atividade, carga_horaria)
#	VALUES('Xeque-Mate', '30')";
#if($executar = mysqli_query($conexao, $query))
#	echo "Executou com sucesso! (inserção atividade)<br>";
#else echo "Falha ao executar (inserção atividade)<br>";

# Inserir participante_atividade
$query = "INSERT INTO PARTICIPANTE_ATIVIDADE(id_participante, id_atividade) 
	VALUES(1, 1)";
if($executar = mysqli_query($conexao, $query)) 
	echo "Success (insert participante_atividade)<br>";

*/

for($i=2; $i<6; $i++)
if(mysqli_query($conexao, "INSERT INTO PARTICIPANTE_ATIVIDADE(id_participante, id_atividade) 
	VALUES($i, 1)"))
	echo 'Success (for para preencher tabela', $i,')<br>';