/*!
 * \file
 * \brief Заголовочный файл класса регулярного выражения
 * \author InvalidPointer
 *
 * Данный файл содержит в себе определение класса, в котором реализованы обёртки над классом,
 * занимающимся проверкой строк, в виде функций Regexp::match() и Regexp::search()
*/
#ifndef MYGREP_MYGREP_H
#define MYGREP_MYGREP_H


#include "LexicalAnalyzer.h"
#include "SyntaxAnalyzer.h"
#include "RegexpChecker.h"

/*!
 * \brief Класс регулярного выражения
 *
 * Класс регулярного выражения служит для проверки строк на соответствие регулярному выражению
 * и поиска подстроки, соответствующей регулярному выржению, в заданной строке
 */
class Regexp
{
private:
    vector<token> sv;       ///< Вектор с преобразованными лексемами
public:
    /*!
     * Конструктор регулярного выражения
     * \param[in] pattern Регулярное выражение в строковом виде
     */
    Regexp(const string &pattern);
    ~Regexp() {}

    /*!
     * Проверяет строку на соответствие регулярному выражению
     *\param[in] target Строка, которую необходимо проверить
     *
     * \return Результат проверки
     */
    bool match(const string &target) const;

    /*!
     * Ищет подстроку, соответствующую регулярному выражению, в строке
     *\param[in] target Строка, в которой производится поиск
     *
     * \return Результат поиска
     */
    rc_result search(const string &target) const;
};


#endif //MYGREP_MYGREP_H
