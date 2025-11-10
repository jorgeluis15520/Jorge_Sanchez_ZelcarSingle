# Jorge Sanchez

Prueba Tecnica Zelcar Games <br />

Controles: <br />
WASD -> Movimiento <br />
Left Shift -> Correr <br />
Mouse -> Mover Camara <br />
I -> Abrir y Cerrar inventario <br />
<br />
-- Cerca de un animal salvaje-- <br />
J-> Atacar <br />
K-> Capturar <br />
<br />
-Puedes ver en la consola si la captura falla  o no con los datos de como se calcula el CaptureRatio <br />
-Tambien puedes ir abriendo y cerrando el inventario para ver si se agrego la mascota <br />
<br />
-- Inventario --<br />
Al hacer click en un slot aparecera la mascota selecionada al lado tuyo <br />

Video: https://drive.google.com/file/d/1yPCBqPrpGnJb6g2v6gg7muVkJv0hmz-K/view?usp=sharing  <br />

-- Agregar Mascota -- <br />
Para agregar una mascota nueva se debe crear un DataAsset que herede de "PetDataAsset" <br />
Se debe completar los campos: ID, Name, SkeletalMesh y AnimationInstance <br />

-- Crear un Anim Instance --
Para agregar un nuevo anim instance para una mascota, selection el "ABP_PetTemplate" <br />
Crear un blueprint child skeletal que herede de ese template con el skeletal de la nueva mascota <br />
Para el AnimationBlueprint que acabas de crear es necesario que crees un BlendSpaceAnimation <br />
Este BlendSpace es para el locomotion de la mascota IDLE-WALK-RUN. Axis debe ser el GroundSpeed <br />
IDLE-> 0.f , WALK-> 125.f y RUN -> 300.F <br />
Ahora en un AnimationBlueprint en AnimOverride ve despliega hasta Locomotion y agrega el BS que acabas de crear <br />
Ahora ese AnimationBlueprint lo puedes asignar a cualquier PetDataAsset  para que tenlas las animaciones de idle, walk y run de la nueva mascota <br />
