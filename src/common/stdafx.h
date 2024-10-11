#pragma once


#define Q_PROPERTY_AUTO_P(TYPE, M)                                                                 \
    Q_PROPERTY(TYPE M MEMBER m_##M NOTIFY M##Changed)                                               \
public:                                                                                            \
    Q_SIGNAL void M##Changed();                                                                    \
    void M(TYPE in_##M) {                                                                          \
        m_##M = in_##M;                                                                             \
        Q_EMIT M##Changed();                                                                       \
    }                                                                                              \
    TYPE M() {                                                                                     \
        return m_##M;                                                                               \
    }                                                                                              \
                                                                                                   \
private:                                                                                           \
    TYPE m_##M;

#define Q_PROPERTY_AUTO(TYPE, M)                                                                   \
    Q_PROPERTY(TYPE M MEMBER m_##M NOTIFY M##Changed)                                              \
public:                                                                                            \
    Q_SIGNAL void M##Changed();                                                                    \
    void M(const TYPE &in_##M) {                                                                   \
        m_##M = in_##M;                                                                            \
        Q_EMIT M##Changed();                                                                       \
    }                                                                                              \
    TYPE M() const {                                                                               \
        return m_##M;                                                                              \
    }                                                                                              \
                                                                                                   \
private:                                                                                           \
    TYPE m_##M;


#define Q_PROPERTY_READONLY_AUTO(TYPE, M)                                                          \
    Q_PROPERTY(TYPE M READ M NOTIFY M##Changed FINAL)                                              \
public:                                                                                            \
    Q_SIGNAL void M##Changed();                                                                    \
    void M(const TYPE &in_##M) {                                                                   \
        m_##M = in_##M;                                                                             \
        Q_EMIT M##Changed();                                                                       \
    }                                                                                              \
    TYPE M() {                                                                                     \
        return m_##M;                                                                               \
    }                                                                                              \
                                                                                                   \
private:                                                                                           \
    TYPE m_##M;
