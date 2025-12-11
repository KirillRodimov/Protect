#include "simplecrypt.h"
#include <QByteArray>

SimpleCrypt::SimpleCrypt(const QString& key) {

    m_key = key.toUtf8();

    if (m_key.isEmpty()) m_key.append('x');
}

QByteArray SimpleCrypt::encryptToByteArray(const QString& plaintext) {
    QByteArray plainBytes = plaintext.toUtf8();
    QByteArray result = plainBytes;


    for (int i = 0; i < plainBytes.size(); ++i) {

        result[i] = plainBytes[i] ^ m_key[i % m_key.size()];
    }


    return result.toBase64();
}

QString SimpleCrypt::decryptFromByteArray(const QByteArray& encryptedBase64) {

    QByteArray encrypted = QByteArray::fromBase64(encryptedBase64);
    QByteArray result = encrypted;


    for (int i = 0; i < encrypted.size(); ++i) {
        result[i] = encrypted[i] ^ m_key[i % m_key.size()];
    }

    return QString::fromUtf8(result);
}
