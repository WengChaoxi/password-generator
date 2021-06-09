#ifndef CRYPTO_H
#define CRYPTO_H

#include <QObject>

#define CRYPTO_DEFAULT_KEY "h3110_w0r1d"

class Crypto : public QObject
{
    Q_OBJECT

public:
    explicit Crypto(QObject *parent = nullptr);
    QByteArray xorWithKey(QByteArray data, const QByteArray &key);
    QByteArray xorWithUniqueKey(QByteArray data);
    QByteArray md5(const QByteArray &data);
    QByteArray sha256(const QByteArray &data);
    QString toBase64Str(const QByteArray &data);
    QByteArray fromBase64Str(const QString &str);

private:
    QByteArray _unique_key;

    QByteArray hash(const QByteArray &data, const QString &hash_type);
    void initUniquetKey();

signals:

public slots:
};

#endif // CRYPTO_H
