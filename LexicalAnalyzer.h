/*!
 * \file
 * \brief Заголовочный файл лексического анализатора
 * \author InvalidPointer
 *
 * Данный файл содержит в себе определение класса лексического анализатора
*/
#ifndef MYGREP_LEXICALANALYZER_H
#define MYGREP_LEXICALANALYZER_H


#include <string>
#include <vector>
#include <cctype>
#include <stdexcept>

#include "token.h"

using namespace std;

/*!
 * \brief Лексический анализатор
 *
 * Лексический анализатор преобразует исходное регулярное выражение в последовательность лексем, проверяя экранирование специальных символов.
 */
class LexicalAnalyzer
{
private:
    /*!
     * Проверяет, является ли символ специальным
     * \param[in] ch Проверяемый символ
     *
     * \return Результат проверки
     */
    static bool isspecial(char ch);

    /*!
     * Проверяет, является ли строка числом
     * \param[in] s Проверяемая строка
     *
     * \return Та же строка
     *
     * \throw std::invalid_argument В случае, если строка не является числом
     * \throw std::out_of_range В случае, если записанное в строке число не может поместиться в тип int
     */
    static string is_num(const string &s);
public:
    LexicalAnalyzer() {}
    ~LexicalAnalyzer() {}

    /*!
     * Производит лексический анализ регулярного выражения
     * \param[in] s Анализируемое выражение
     *
     * \return Вектор, составленный из лексем регулярного выражения
     *
     * \throw std::invalid_argument В случае некорректных входных данных
     */
    static vector<token> analyze(const string &s);
};


#endif //MYGREP_LEXICALANALYZER_H
