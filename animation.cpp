#include "animation.h"

Animation::Animation(const QPoint &position) :
    m_frame(0), m_position(position)
{

}

QPixmap Animation::nextFrame()
{
    if(m_frame < m_frames.size() - 1)
    {
        m_frame ++;
    }
    return m_frames.at(m_frame);
}

bool Animation::animationDone() const
{
    return (m_frame == m_frames.size());
}

