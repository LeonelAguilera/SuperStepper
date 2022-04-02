# SuperStepper
Los motores paso a paso son máquinas muy interesantes. Permiten un control de posición en lazo abierto con una precisión excepcional, precisión que se puede incrementar a través de software. Para ello esxiste un gran abanico de drivers con el objetivo de facilitar su control, sin embargo, estos suponen un coste extra que según el proyecto puede no ser despreciable, o el no tenerlos disponibles cuando necesitas hacer una prueba rápida puede retrasar el proyecto. Por estas y muchas más razones es conveniente ser capaz de controlar estos motores sin el uso de drivers, los cuales reemplazaré (principalmente) con la unidad de control más abundante en los laboratorios maker: El Arduino UNO.

Con estas condiciones la principal limitación es evidente, los Arduinos UNO tienen una salida máxima de 5V 40mA por pin, mucho menos de lo que la mayoría motores paso a paso necesitan para funcionar. Para salvar esta limitación se añadirá el uso de un puente H por fase. En los distintos códigos (salvo que se indique lo contrario) en lo referido al control del puente H se usará la notación de los módulos de puente H basados en el L298N:
  ·**ENx:** Enable del puente H "x" (ejemplo: ENA es el _enable_ del puente H **A**)
  ·**INy/INy+1:** Activa un lado u otro del puente H número 2·y (ejemplo: IN3 activa un lado del puente H **B** e IN4 activa el otro lado)

Otra de las limitaciones de este sistema es la falta de protecciones (incluso los drivers de motores paso a paso más baratos incluyen protección contra sobrecorriente, muy importante a la hora de mantener la posición del motor), la inclusión de estas se irá desarrollando junto al proyecto.

Actualmente hay 3 códigos en el repositorio:

##BaseStepper
Control muy básico de motor paso a paso bipolar, permite elegir entre no usar micropasos y micropasos 1/2 (se recomienda la segunda opción por estabilidad), es un código bastante sencillo, fácil de entender, fiable y fácil de implementar

##Stepper_64
Control un poco más avanzado de motores paso a paso bipolares, está fijo* a micropasos de 1/64, sin embargo requiere de gran cantidad de pines (6 por motor, dos de ellos PWM), sin embargo esta alta necesidad se puede reducir desconectando IN2 e IN4 del arduino y conectándolos directamente a IN1 e IN3 (respectivamente) con una compuerta lógica NOT entre los pines (es decir IN2 = NOT(IN1) & IN4 = NOT(IN3).

##Stepper_256
Control exprimiendo al máximo al Arduino fijo* a 1/256 micropasos, para obtener la resolución de PWM suficiente se han modificado directamente los registros del controlador para que su contador de 16 bits (que por defecto se usa como contador de 8 bits) sea usado como contador de 10 bits. Este código usa la misma cantidad de pines que el Stepper_64 (los cuales pueden reducirse a través del mismo método) con la limitación extra de que para los _Enable_ solo se pueden usar los pines 9 y 10, además puede que sea incompatible con la librería Servo.h y similares. Esto es más una prueba de capacidades que un sistema de control real, no veo recomendable usar este código (al menos en su estado actual) para un proyecto ya que cada vez que sea necesario mover el motor o bien se hará de forma excesivamente lenta o bien será necesario parar la ejecución de todo lo que esté haciendo el arduino en ese momento, ya que por la gran cantidad de micropasos que se tienen que dar para completar una vuelta este código es especialmente sensible al tiempo de ejecución, limitando al uso del arduino a poco más que un driver por sí mismo, el cual para el caso, es más caro, engorroso y propenso a fallos y problemas que un driver real.
