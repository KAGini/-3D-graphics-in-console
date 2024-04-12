Небольшая CLI бродилка
![Screenshot from 2024-04-11 18-48-26](https://github.com/KAGini/Console3D/assets/105926821/244d7a9c-7fd3-434e-a7a4-b7c12dd3db59)
Необходима ОС Linux!
# Начало работы
1. Клонирование репозитория
   ```git clone https://github.com/KAGini/Console3D.git; cd Console3D```
2. Создание файла polygons.txt <br />
   1.Создайте файл polyogn.txt: ```touch polygons.txt```<br />
   2.Откройте его в текстовом редакторе: <br />
   `vi polygons.txt` <br />
   `vim polygins.txt`<br />
   `nvim polygon.txt`<br />
   `nano polygons.txt`<br />
   3. Заполните его в формате
      `n` - количество стен в виде многоугольников<br />
      Далее идут `n` кусков вида<br />
      `m` - число вершин многоугольника<br />
      `m` пар чисел `x y` - координаты каждой вершины
4. Запустите<br />
   ```chmod +x run.sh```<br />
   ```./run.sh```
