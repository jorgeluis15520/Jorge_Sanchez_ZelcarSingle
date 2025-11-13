# Jorge Sanchez

Prueba Tecnica Zelcar Games <br />
<br />
Video: https://drive.google.com/file/d/1fHZtetuopXqDnIUwu6Q9EJ3z2P7jRV2w/view?usp=sharing
<br />
Controles: <br />
WASD -> Movimiento <br />
Left Shift -> Correr <br />
Mouse -> Mover Camara <br />
I -> Abrir y Cerrar inventario <br />
<br />
-- Combate -- <br />
J-> Atacar <br />
K-> Capturar <br />
L-> Escapar <br />
I-> CambiarMascota <br />
<br />
-Puedes ver en la consola si la captura falla  o no con los datos de como se calcula el CaptureRatio <br />
-Tambien puedes ir abriendo y cerrando el inventario para ver si se agrego la mascota <br />
<br />
-- Inventario --<br />
Al hacer click en un slot aparecera la mascota selecionada al lado tuyo <br />
 <br />
-- Agregar Mascota -- <br />
Para agregar una mascota nueva se debe crear un DataAsset que herede de "PetDataAsset" <br />
Se debe completar los campos: ID, Name, SkeletalMesh, AnimationInstance y BasicAttackMontage <br />
 <br />
 
-- Crear un Anim Instance --<br />
Para agregar un nuevo anim instance para una mascota, selection el "ABP_PetTemplate" <br />
Crear un blueprint child skeletal que herede de ese template con el skeletal de la nueva mascota <br />
Para el AnimationBlueprint que acabas de crear es necesario que crees un BlendSpaceAnimation <br />
Este BlendSpace es para el locomotion de la mascota IDLE-WALK-RUN. Axis debe ser el GroundSpeed <br />
IDLE-> 0.f , WALK-> 125.f y RUN -> 300.F <br />
Ahora en un AnimationBlueprint en AnimOverride ve despliega hasta Locomotion y agrega el BS que acabas de crear <br />
Ahora ese AnimationBlueprint lo puedes asignar a cualquier PetDataAsset  para que tenlas las animaciones de idle, walk y run de la nueva mascota <br />

-- Animation Mongate -- <br />
Las mascotas necesitan un animation montage para su ataque basico, se debe crear uno en el skeletal de la mascota<br />
dejar el SectionName como "Default" y agregar un AnimNotify al final de la animacion de ataque. <br />
Este AnimMontage debe triggerear el metodo "AttackEnd" de la masco, entonces se debe setear en el evengrapht del AnimationInstance Blueprint de la mascota. <br />

-- Nota -- <br />
La idea inicial era usar GAS para los ataques y stats, pero de la forma en que esta hecho se puede implementar despues <br />
Es decir en el DataPet en lugar de usar Montages para los ataques se usarian GameplayAbility <br />
Pasariamos estas habilidades por la Data y se agregarian en el AbilitySystemCompoenent de la mascota <br />
Asimismo el AttributeSet para los stats health, damage, etc <br /> 
Por otro lado el DataAsset se puede cambiar por un DataTable para manejar mayor cantidad de mascotas<br />
Finalmente, se deberia crear un clase para manejar el combate, una que comunique las acciones  con el UI y el Player mediante delegates <br/>
De esta forma sabriamos cuando termina el cooldown de habilidad, se esta capturadon, el estado de las mascotas, inicio y final de combate, etc <br />
