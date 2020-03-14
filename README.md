# Space Worms

Zespołowy projekt na Inżynierię Oprogramowania MIMUW 2020.
C++ z biblioteką SFML.

## Autorzy
Rafał Czarnecki
Kajetan Husiatyński
Michał Szczęśniak
Anita Śledź

## Streszczony opis

Gra 2D hotseat w której gracz steruje flotą statków kosmicznych, a jego celem jest zestrzelenie wrogich flot.
W przestrzeni kosmicznej istnieją obiekty, które wpływają na tor lotu pocisku.

# Opis szczegółowy

## Tury w grze
Gracz w trakcie swojej tury ma wyznaczony czas. Podczas niego może przesuwać swoje statki indywidualnie rozdzielając dany mu limit. Turę kończy po wystrzeleniu z JEDNEGO ze swoich statków. Jeśli w momencie wystrzelenia gracz miałby jeszcze czas do wydania to zostaje on przeznaczony na początkowy ruch pocisku.

## Ruch pocisku
Pocisk porusza się w kwantach czasu w których oblicza zmianę swojego położenia oraz swojej prędkości. Na początku pocisk ma określoną prędkość i kierunek. Pocisk kończy swój ruch po uderzeniu w inny obiekt.

## Obiekty
Na planszy znajdują obiekty posiadające różne właściwości:

### Statki (spaceship)
Statki kontrolowane przez gracza. Potrafią się przemieszczać i po kolizji z pociskiem otrzymują obrażenia.

### Pociski (bullets)
Pociski mogą kolidować ze sobą nawzajem. Działa na nie grawitacja.

### Czarne dziury (black hole)
Kolizja z czarną dziurą powoduje zniszczenie obiektu (lub jego części). Moc czarnej dziury jest definiowany przez masę.

## Obiekty które można dodać w przyszłości

### Wektory (vector)
Po najechaniu kursorem na pocisk możemy zobaczyć jego aktualny wektor prędkości.

### Bonusy (bonus)
Jeśli gracz trafi w bonus może otrzymać bonus w postaci np, przewidywania toru lotu pocisku, odkrycia wektorów, rozdwojenie pocisku, więcej czasu, pociski do broni, itp.

### Ślad pocisku (trace)
Obiekt cząsteczkowy pojawiający się za lecącym pociskiem. Stopniowo zanika po upływie czasu in-game.

### Asteroidy (asteroid)
Obiekty które nie oddziałowują grawitacyjnie na pociski, ale kolidują z nimi. Niszczą się częściowo?

### Tunele (Wormhole)
Punkty połączone, wlot w jedne miejsce powoduje wylot drugim.

### Białe dziury (white hole)
Obiekty odwrotne do czarnych dziur. Odpychają.

### Obiekty kompozytowe
Ruchome dziury, asteroidy, bonusy. Asteroidy, tunele oddziałowujące grawitacyjnie.

## Bronie
Gracz będzie miał do dostępnu wiele broni różniącymi się szybkością, wzorem, siłą i dostępnością.

#Inne pomysły na przyszłość
Edytor poziomów
Strzelnica treningowa / wyzwaniowa