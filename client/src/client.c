#include "client.h"

//NOTAS:
//- Si usamos un readline, recordar usar un free (1)
//- El objetivo del trabajo es ingresar lineas e ir loggeandolas. Cuando la linea que recibe es '/0' (es decir)
//no insertamos nada, se debe acabar el programa. Por lo tanto la condicion de corte es '/0'

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();
	log_info(logger, "Logger iniciado");

	config = iniciar_config();
	log_info(logger, "Configuracion iniciada");

	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	valor = config_get_string_value(config, "VALOR");
	
	// log_info(logger, ip);
	// log_info(logger, puerto);
	// log_info(logger, valor);

	// leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	//enviar CLAVE al servirdor
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger =  log_create("tp0.log", "Cliente", 1, LOG_LEVEL_DEBUG);
	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = config_create("tp0.config");
	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;
	leido = readline(">");
	log_info(logger, leido);
	free(leido);
}

void paquete(int conexion)
{
	char* leido = readline(">");
	while (!strcmp(leido, "")) {
		t_paquete* paquete = crear_paquete();
		agregar_a_paquete(paquete, leido, strlen(leido + 1));
		enviar_paquete(paquete, conexion);
		eliminar_paquete(paquete);
	}
	free(leido);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
	log_destroy(logger);
	config_destroy(config);
	liberar_conexion(conexion);
}
