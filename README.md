#Лабараторна №1
#Iдеальне хешування

Iдеальне хешування - метод хешування розроблений для статичних даних, якi нiколи не змiнюються, або змiнюються дуже рiдко.
Таке хешування даватиме час пошуку О(1) у найгiршому випадку.
Суть цього методу полягає у код у використаннi двох рiвнiв хешування(у моєму кодi - L1HT(Level 1 Hash Table) та L2HT(Level 2 Hash Table)

![Perfct Hash Representation](http://picua.org/img/2018-02/07/umwe9if67xotjvaq7cto1ze6j.png)

#Внесення ключа до таблицi проходить наступним чином:
1. За допомогою хеш функцiї, обраної с унiверсального класу хеш-функцiй
![Universal Hash Function Class](http://picua.org/img/2018-02/07/qld4oib0ho6nx0kiluktxtmc3.png)
хешуватимемо значення ключа до L1HT, таблицi першого рiвня. Кожна(тут - випадково обрана) пара А та В даватимуть iншу хеш-функцiю.
При цьому значення р завжди залишатиметься статичним, пiсля того, як буде обрано - це просте число, таке, що значення будь-якого ключа входить у множину {0,1, .. ,p-1}.
2. Використовуючи знайдений iндекс складемо внутрiшню таблицю. Для цього знову оберемо випадковi A та В, а m замiнимо на кiлькiсть хешованих у цю комiрку L1HT значень пiднесену до квадрату(для уникнення колiзiй). Використовуючи новоотриману хеш-функцiю визначимо
iндекс ключа у L2HT.
  #!Важливо
  Розмiр m^2 обрано не випадково - при такому розмiрi L2HT матимемо шанс отримати колiзiю не бiльше нiж 1/2(парадокс днiв народження)
3.Через досить велику ймовiрнiсть колiзiй на другому рiвнi ми повиннi перевiряти отриманi таблицi на вiдсутнiсть колiзiй. Якщо нас спiткала невдача, та колiзiю все ж таки отримано - повторимо крок 2, з новими А та В, i так аж доки не матимемо таблицi без колiзiй.

#Пошук

Пошук по таблицi такий же, як i внесення елементу, але без побудови таблиць:
1. Приймаємо на вхiд значення ключа.
2. Використовуємо хеш-функцiю визначену для L1HT щоб отримати iндекс у таблицi першого рiвня
3. Використовуємо збережену ранiше iнформацiю про значення А та В, використання яких при створеннi таблицi L2HT дало таблицю без колiзiй.
4. За допомогою цих даних знову хешуємо вхiдне значення ключа
5. За отриманим iндексом матимемо необхiдне нам значення для вхiдного ключа.
