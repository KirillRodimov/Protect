#include "simplecrypt.h"
#include <QByteArray>

SimpleCrypt::SimpleCrypt(const QString& key) {
    // Преобразуем ключ в байты для удобства работы
    m_key = key.toUtf8();
    // Если ключ пустой, делаем хотя бы один байт
    if (m_key.isEmpty()) m_key.append('x');
}

QByteArray SimpleCrypt::encryptToByteArray(const QString& plaintext) {
    QByteArray plainBytes = plaintext.toUtf8();
    QByteArray result = plainBytes;

    // Применяем XOR для каждого байта
    for (int i = 0; i < plainBytes.size(); ++i) {
        // Используем ключ циклически: i % m_key.size()
        result[i] = plainBytes[i] ^ m_key[i % m_key.size()];
    }

    // Возвращаем в кодировке Base64, чтобы можно было хранить как текст
    return result.toBase64();
}

QString SimpleCrypt::decryptFromByteArray(const QByteArray& encryptedBase64) {
    // Декодируем из Base64
    QByteArray encrypted = QByteArray::fromBase64(encryptedBase64);
    QByteArray result = encrypted;

    // Снова применяем XOR для расшифровки
    for (int i = 0; i < encrypted.size(); ++i) {
        result[i] = encrypted[i] ^ m_key[i % m_key.size()];
    }

    return QString::fromUtf8(result);
}
