/*!
 * \file
 * \brief Заголовочный файл класса, проверяющего строки
 * \author InvalidPointer
 *
 * Данный файл содержит в себе определение класса, который реализует механизм проверки
 * соответствия строки с регулярным выражнием
*/
#ifndef MYGREP_REGEXPCHECKER_H
#define MYGREP_REGEXPCHECKER_H


#include <vector>
#include <string>
#include <stdexcept>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "token.h"
#include "rc_result.h"

using namespace std;

/*!
 * \brief Класс, проверяющий строку на соответствие регулярному выражению
 *
 * Класс последовательно выполняет операции регулярного выражения, с учётом их приоритетов, проверяя таким образом строку
 * на соответствие
 */
class RegexpChecker
{
private:
    bool child;                             ///< Показывает, является ли даный процесс дочерним

    const vector<token> *sv;                ///< Указатель на вектор с преобразованными лексемами
    vector<token>::const_iterator svit;     ///< Итератор, используемый для обхода вектора лексем
    const string *target;                   ///< Указатель на строку, которую необходимо проверить
    const string::const_iterator btit;      ///< Итератор, указывающий на место в строке, с которого начинается проверка
    string::const_iterator tit;             ///< Итератор, используемый для перемещения по строке

    bool search;                            ///< Показывает, находится ли класс в режиме поиска подстроки

    /*!
     * Выполняет текующую операцию
     *
     * \return Результат операции
     */
    bool check_op();

    /*!
     * Проверяет на соответствие последовательность литералов
     *
     * \return Результат операции
     */
    bool op_str();

    /*!
     * Выполняет операцию перечисления
     *
     * \return Результат операции
     */
    bool op_enum();

    /*!
     * Выполняет операцию конкатенации
     *
     * \return Результат операции
     */
    bool op_cat();

    /*!
     * Выполняет операцию итерирования
     * \param[in] min Минимально необходимое количество итераций
     * \param[in] max Максимальное количество итераций
     *
     * \return Результат операции
     */
    bool op_iter(int min = 0, int max = -1);

    ///Пропускает текущую операцию
    void skip_op();
public:
    /*!
     * Конструктор класса
     * \param[in] v Указатель на вектор лексем регулярного выражения в префиксной форме
     * \param[in] s Указатель на строку, которую необходимо проверить
     * \param[in] sit Итератор, который используется для задания начальной позиции для обработки строки
     * \param[in] search Определяет режим проверки: сопоставление или поиск
     */
    RegexpChecker(const vector<token> *v, const string *s, string::const_iterator sit, bool search = false);
    ~RegexpChecker() {}

    /*!
     * Запускает проверку
     *
     * \return Результат проверки
     */
    rc_result check();
};


#endif //MYGREP_REGEXPCHECKER_H
