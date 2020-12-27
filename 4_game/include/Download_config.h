/**
\file
\brief Этап загрузки информации с конфигурационных файлов
Информация загружается с файлов config/mode.txt, config/config.txt, config/param.txt
 Если информация не загружена, то загружается иноформация по умолчанию
*/

#pragma once

#include <fstream>
#include "my_stdlib.h"
#include "mission_classes.h"

/// Функция загрузки с файлов
/**
\param[out] c, p, m Структуры инормации
\return true, если загрузка прошла успешно
\return false, если нет и загружена информация по умолчанию
*/
bool download_info(config& c, param_mission& p, mode_mission& m);