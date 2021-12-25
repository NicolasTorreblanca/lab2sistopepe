//Entrada: Float x INT x INT x INT x INT
//Funcionamiento: Permite calcular el efecto del impacto de una particula en una celda especifica
//Salida: un flotante, que indica la energia resultante en la celda despues del impacto

float impacto(float energiaInicial, int energiaParticula, int cantidadCeldas, int posCelda, int posParticula){
    float newEnergia = energiaInicial + (1000*energiaParticula)/(cantidadCeldas*sqrtf((float)(abs(posParticula-posCelda) + 1)));
    return newEnergia;
}
