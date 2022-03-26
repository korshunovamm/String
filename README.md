## Класс String

Класс String - упрощенный аналог std::string. Класс поддерживает следующий функционал:
* Конструктор по умолчанию - создает пустую строку, никакой памяти не выделяется!
* Конструктор, принимающий size и character (именно в этом порядке) - создает строку длины size, заполненный символами character
* Конструктор от const char*, для того, чтобы узнать длину C-style строки, используйте функцию strlen
* Правило "трех":
    1. Конструктор копирования
    2. Копирующий оператор присваивания
    3. Деструктор
* Метод Clear() - устанавливает размер в 0, деаллокации выделенной памяти при этом не происходит
* Метод PushBack(character) - добавляет букву character в конец строки
* Метод PopBack() - удаляет последнюю букву. В случае пустой строки должен ничего не делать, хотя для std::string это будет UB
* Метод Resize(new_size) - изменяет размер на new_size. Если вместимость не позволяет хранить столько символов, то выделяется новый буфер с вместимостью new_size.
* Метод Resize(new_size, character) - то же, что и Resize(new_size), но в случае new_size > size заполняет недостающие элементы значением character.
* Метод Reserve(new_cap) - изменяет вместимость на max(new_cap, текущая вместимость) (если new_cap <= текущая вместимость, то делать ничего не нужно). Размер при этом не изменяется.
* Метод ShrinkToFit() - уменьшает capacity до size (если capacity > size)
* Метод Swap(other) - обменивает содержимое с другой строкой other. Должен работать за O(1)
* Константный и неконстантный оператор доступа по индексу []. Неконстантный должен позволять изменять полученный элемент (a[1] = 5)
* Методы Front() и Back() - доступ к первому и последнему символам (тоже по две версии).
* Метод Empty() - true, если строка пустая (размер 0)
* Метод SizePrivate() - возвращает размер
* Метод Capacity() - возвращает вместимость
* Метод Data() - возвращает указатель на начало массива.
* Операторы сравнения (<, >, <=, >=, ==, !=), задающие лексикографический порядок
* Операторы + и += для конкатенации строк. Например, "ab" + "oba" = "aboba".
* Оператор умножения на число. Принимает строку str и число n (именно в таком порядке) и вернет строку вида str +  ... + str (n раз).

* Операторы ввода из потока и вывода в поток.
* Метод std::vector<String> Split(const String& delim = " ") - аналог сплита в питоне.
* Метод String Join(const std::vector<String>& strings) - аналог джоина в питоне.


В тесты включены проверки функциональности (методы работают так как требует условие), проверка эффективности реализации (что значит эффективно описано выше), проверка корректности работы с памятью (утечки памяти, обращения к памяти не принадлежащей процессу будут приводить к провалу)