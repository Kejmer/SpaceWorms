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