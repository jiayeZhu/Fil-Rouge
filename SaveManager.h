#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include "NeuralNetwork.h"
#include <QString>
#include <QtXml>

static const QString savePath("../save/");

class SaveManager
{
public:
    SaveManager();
    int SaveNetwork(const NeuralNetwork& nn, QString neuralNetworkName="temp");
    NeuralNetwork LoadNetwork(QString neuralNetworkName="temp");
    void parseNeuronalNetwork(QXmlStreamReader& reader);
};

#endif // SAVEMANAGER_H
