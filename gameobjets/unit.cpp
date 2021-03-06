#include "unit.h"

Unit::Unit()
{
    m_position = QPoint(0,0);

    m_maxLife = 100;
    m_life = m_maxLife;
    m_lifeAnim = m_maxLife;
    m_dead = false;
    m_deathDuration = 1000;
    m_isResurecting = false;

    m_invulnerable = false;
    m_invulnerabilityDuration = 3000;
}

int Unit::life() const
{
    return m_life;
}

void Unit::setLife(int life)
{
    m_life = life;
}

int Unit::maxLife() const
{
    return m_maxLife;
}

void Unit::setMaxLife(int maxLife)
{
    m_maxLife = maxLife;
}

int Unit::lifeAnim() const
{
    return m_lifeAnim;
}

void Unit::setLifeAnim(int lifeAnim)
{
    m_lifeAnim = lifeAnim;
}

void Unit::updateLifeAnim()
{
    if(m_lifeAnim > m_life) m_lifeAnim --;
    if(m_lifeAnim < m_life) m_lifeAnim ++;

    if((m_lifeAnim == 0)&&(!m_isResurecting))
    {
        QTimer::singleShot(m_deathDuration, this, SLOT(resurrect()));
        m_isResurecting = true;
        m_invulnerable = true;
    }
    if(m_lifeAnim == m_maxLife) m_dead = false;
}

bool Unit::dead() const
{
    return m_dead;
}

void Unit::setDead(bool dead)
{
    m_dead = dead;
}

void Unit::takeDamage(int damage)
{
    if(m_invulnerable) return;
    m_life -= damage;
    if(m_life <= 0)
    {
        m_life = 0;
        setDead(true);
    }
}

bool Unit::isUnit() const
{
    return true;
}

void Unit::resurrect()
{
    m_life = m_maxLife;
    m_deathDuration += 200;
    m_isResurecting = false;
    m_position = m_lastValidPosition;
    QTimer::singleShot(m_invulnerabilityDuration, this, SLOT(removeInvulnerability()));
}

void Unit::removeInvulnerability()
{
    m_invulnerable = false;
}
int Unit::invulnerabilityDuration() const
{
    return m_invulnerabilityDuration;
}

void Unit::setInvulnerabilityDuration(int invulnerabilityDuration)
{
    m_invulnerabilityDuration = invulnerabilityDuration;
}

int Unit::deathDuration() const
{
    return m_deathDuration;
}

void Unit::setDeathDuration(int deathDuration)
{
    m_deathDuration = deathDuration;
}

bool Unit::invulnerable() const
{
    return m_invulnerable;
}

void Unit::setInvulnerable(bool invulnerable)
{
    m_invulnerable = invulnerable;
}


void Unit::setPosition(const QPoint &position, bool isValid)
{
    if(isValid)
        m_lastValidPosition = position;
    m_position = position;
}

void Unit::setPosition(int x, int y, bool isValid)
{
    setPosition(QPoint(x,y), isValid);
}

QPoint Unit::lastValidPosition() const
{
    return m_lastValidPosition;
}

void Unit::setlastValidPosition(const QPoint &lastValidPosition)
{
    m_lastValidPosition = lastValidPosition;
}




