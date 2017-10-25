Шаблонный класс-матрица. В конструкторе задается количество рядов и строк (+ есть контрукторы и операторы копирования и перемещения). Поддерживаются операции: 

получить количество строк/столбцов, 

получить конкретный элемент ([][]),

умножить на вектор ( *= или *, в качестве вектора использовать класс std::vector\<T\>, T - тот же тип, что и у 
элементов матрицы), 

умножить на число ( *=, число - объект того же типа, что и элементы матрицы), 

сравнение на равенство/неравенство.
