#include "./Util/test/TestInclude.h"
#include <unity.h>

static Task* land = new Landing();
static bool TTM = false; // Test Task Motor flag


/*controllare il primo stadio --- 2. che il led sia attivo, che le porte siano chiuse e ricevano il comando di doversi aprire e che lcd abbia la scritta,




3. attivare il wait for drone e controllarne l'effettiva attesa

2-3 controllare che la porta sia aperta

4. quando il drone è atterrato controllarne la presenza, il reset dei sensori , controllare la chiusura del landing


 1 . controllare che il pir riceva il  segnale del drone*/

