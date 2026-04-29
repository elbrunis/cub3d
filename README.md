## tareas a empezar

- [] pasar a limpio el resto de el codigo
- [] estructurar como vamos a organizar el parseo ejemplo:      
         1	check_extension	         Comprueba que el archivo acabe en .cub.
         2	parse_identifiers	Guarda las rutas de XPM y los colores RGB.
         3	parse_map	Lee el mapa en un char ** (array de strings).
         4	validate_map	Comprueba muros, jugador único y caracteres válidos.
   una vez esto pensar como vamos structurar toda la logica
- [] hacer parseo
- [] terminar la parte de las texturas
- [] pulir norminette finish


















-[]ponte con lo de mover el jugador es decir las funciones de key_hook dale un repaso de lo q habia q hacer en el gemini en el chat preguntale volvamos a lo de el mapa en 2d ponme los pasos etc y empiezas con eso, ten cuidado con los errores tonteria por q te has tirado mas de 1h con un error que resultaba ser una tonteria



-[] mirar a ver si con un hilo puedo gestionar bien el tema de terminar el jeugo de golpe sabes para q no tenga q ver el if osea q constantemente este verificando si termino el juego



 - [] renderizar un mapa basico sin texturas ni movimientos ni verificacion de si es correcto
    - [] mirar el video para entender cada parte y ayudarme con chatgpt para entenderlo(te recomiendo hacerlo con un nuevo chat, pasandole el      enlace)
    - []
    - [] primero hay q imprimir el mapa en 2 d
    - [] despues hay q imprimir el personaje como un cuadrado q se mueve y tiene una flecha q apunta
    - [] despues esa flecha q apunta tiene q detectar las paredes y no dejar de imprimir cuando toque las paredes (bucle)
    - [] una vez tenemos esa flecha la multipicamos para q sean varias flechas
    - [] una vez tenemos todo eso hacemos la transformacion a 3d a traves de las formulas necesarias
    - [] 
    - []
 - [] crear un /FOLDER_EXPLANATION.md para cada carpeta como la de parsing


## distribucion de carpetas (gneral)
 - Hooks = movimientos de el jugador
 - parsing = pasar el mapa a un formato ejecutable
 - raycasting = calcular las operaciones necesarias para poder renderizarlo
 - render = imprimir todo el mapa (uso minilibix, imprimir ventana, etc...)
  -main.c = bucle principal para ejecutar el juego a tiempo real



  