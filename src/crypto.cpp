#include "crypto.h"
#include <QCryptographicHash>
#include <QDir>
#include <QHostInfo>
#include <QDebug>

Crypto::Crypto(QObject *parent) : QObject(parent)
{
    initUniquetKey();
}

void Crypto::initUniquetKey()
{
    QByteArray username = QDir::home().dirName().toLocal8Bit();
    QByteArray hostname = QHostInfo::localHostName().toLocal8Bit();
    QByteArray tmp = username+hostname;
    _unique_key = QCryptographicHash::hash(tmp, QCryptographicHash::Md5);
    qDebug() << QDir::home().dirName() << hostname << _unique_key;
}

QByteArray Crypto::xorWithKey(QByteArray data, const QByteArray &key)
{
    int key_len = key.size();
    int data_size = data.size();
    for(int i=0; i<data_size; i++)
    {
        data[i] = data[i]^key[i%key_len];
    }
    return data;
}

QByteArray Crypto::xorWithUniqueKey(QByteArray data)
{
    int key_len = _unique_key.size();
    int data_size = data.size();
    for(int i=0; i<data_size; i++)
    {
        data[i] = data[i]^_unique_key[i%key_len];
    }
    return data;
}

QString Crypto::toBase64Str(const QByteArray &data)
{
    return QString(data.toBase64(QByteArray::OmitTrailingEquals));
}

QByteArray Crypto::fromBase64Str(const QString &str)
{
    return QByteArray::fromBase64(str.toLocal8Bit());
}

QByteArray Crypto::md5(const QByteArray &data)
{
    return hash(data, "md5");
}

QByteArray Crypto::sha256(const QByteArray &data)
{
    return hash(data, "sha256");
}

QByteArray Crypto::hash(const QByteArray &data, const QString &hash_type)
{
    if(hash_type == "md5")
        return QCryptographicHash::hash(data, QCryptographicHash::Md5);
    else if(hash_type == "sha256")
        return QCryptographicHash::hash(data, QCryptographicHash::Sha256);
}
