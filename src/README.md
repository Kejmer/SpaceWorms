# Dodawanie obiektów do świata

* Jeżeli jakiś obiekt ma dedykowaną funkcję dodającą go do świata (np. dziury mają addHoleEntity), to używajmy jej zamiast domyślnej funkcji addEntity
* Jeżeli chcemy dodać jakiś obiekt do kilku DelayedContainerów, to pamiętajmy żeby dodawać do nich ten sam shared_ptr, a nie kilka różnych przechowujących ten sam wskaźnik (funkcja add przyjmująca zwykły wskaźnik zwraca utworzony shared, więc możemy z tego skorzystać)

# Hitboxy

## Tworzenie hitboxów

Zrobione są dwie klasy realizujące hitboxy: BoundingHitbox i ComplexHitbox. 
* BoundingHitbox przyjmuje sf::Shape i obudowywuje go w najmniejszy prostokąt
* ComplexHitbox przyjmuje dowolny sf::Transformable. Prostokąty należy dodać ręcznie za pomocą addRectangle. Ich pozycja jest ustalana względem getPosition() z podanego obiektu sf::Transformable
Aby zaktualizować pozycję hitboxów po zmianie pozycji obiektu do którego są przypisane należy wywołać funkcję Hitbox::update(). 
Jeżeli chcecie zdebugować utworzony hitbox, to możecie go narysować za pomocą Hitbox::draw(sf::RenderWindow &window).

## Obsługa kolizji

Każde entity ma przypisaną pewną kategorię wpływającą na jej zachowanie w momencie kolizji z innymi entity (domyślnie None, co oznacza że nie będzie wchodził z niczym w kolizje). Jeżeli chcecie dodać nową kategorię, zmodyfikujcie Entity::CollisionCategory.
Obsługa kolizji znajduje się w pliku collisions.cpp w funkcji collide.

# Ekrany

Ekrany tworzy się poprzez napisanie klasy dziedziczącej po Screen. Następnie dodawane są one do ScreenHoldera przechowywanego w ScreenManagerze. Ekrany są dodawane na / zdejmowane z końca ScreenHoldera. ScreenManager przegląda dodane ekrany od najpóźniej dodanego w trzech turach (input, update, draw). Dodatkowo każda z tych funkcji zwraca boola - zwrócenie false jest równoważne z przerwaniem przeglądania ekranów umieszczonych przed tym, który zwrócił tą wartość. Np. menu pauzy może zostać dodane po ekranie obsługującym grę i zawsze zwracać false dzięki czemu ekran gry nie będzie aktualizowany dopóki to menu pauzy istnieje. Z kolei np. pole wyboru broni - też dodane po ekranie gry - może chcieć zwracać zawsze true, dzięki czemu gracz będzie mógł dalej sterować swoim statkiem. Program kończy działanie gdy ScreenHolder jest pusty.
