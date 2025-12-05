#ifndef SIMPLECRYPT_H
#define SIMPLECRYPT_H

#include <QString>
#include <QByteArray>

class SimpleCrypt {
private:
    QByteArray m_key;

public:
    SimpleCrypt(const QString& key = "DefaultKey");
    QByteArray encryptToByteArray(const QString& plaintext);
    QString decryptFromByteArray(const QByteArray& encryptedBase64);
};

#endif // SIMPLECRYPT_H
