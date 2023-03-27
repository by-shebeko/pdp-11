# include <stdarg.h>
#include <stdio.h>

//#define ERROR
//#define INFO
//#define TRACE
//#define DEBUG

//#define level ERROR INFO TRACE DEBUG

log(level, format, ...); 

log(level, message);        // функция логирования, в которой указан уровень логирования level 
                            // и сообщение, которое нужно вывести, если этот уровень больше 
                            // и равен установленному пороговому уровню логирования log_level

level set_log_level(level);  // функция, которая устанавливает пороговый уровень логирования как level
                            // и возвращает старый пороговый уровень логирования

