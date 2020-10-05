/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzleWidget.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 11:20:42 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/05 12:31:10 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QPainter>
#include <QStateMachine>
#include <QTimer>
#include <QGraphicsView>
#include <QAbstractTransition>
#include <QRandomGenerator>

using namespace std;

//![15]
class StateSwitchEvent: public QEvent
{
public:
    StateSwitchEvent()
        : QEvent(Type(StateSwitchType))
    {
    }

    explicit StateSwitchEvent(int rand)
        : QEvent(Type(StateSwitchType)),
          m_rand(rand)
    {
    }

    enum { StateSwitchType = QEvent::User + 256 };

    int rand() const { return m_rand; }

private:
    int m_rand;
};
//![15]

//![16]
class QGraphicsRectWidget : public QGraphicsWidget
{
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
               QWidget *) override
    {
        painter->fillRect(rect(), Qt::blue);
    }
};
//![16]

class StateSwitchTransition: public QAbstractTransition
{
public:
    StateSwitchTransition(int rand)
        : QAbstractTransition(),
          m_rand(rand)
    {
    }

protected:
//![14]
    bool eventTest(QEvent *event) override
    {
        return (event->type() == QEvent::Type(StateSwitchEvent::StateSwitchType))
            && (static_cast<StateSwitchEvent *>(event)->rand() == m_rand);
    }
//![14]

    void onTransition(QEvent *) override {}

private:
    int m_rand;
};

//![10]
class StateSwitcher : public QState
{
    Q_OBJECT
public:
    StateSwitcher(QStateMachine *machine)
        : QState(machine), m_stateCount(0), m_lastIndex(0)
    { }
//![10]

//![11]
    void onEntry(QEvent *) override
    {
        int n;
        while ((n = QRandomGenerator::global()->bounded(m_stateCount) + 1) == m_lastIndex)
        { }
        m_lastIndex = n;
        machine()->postEvent(new StateSwitchEvent(n));
    }
    void onExit(QEvent *) override {}
//![11]

//![12]
    void addState(QState *state, QAbstractAnimation *animation) {
        StateSwitchTransition *trans = new StateSwitchTransition(++m_stateCount);
        trans->setTargetState(state);
        addTransition(trans);
        trans->addAnimation(animation);
    }
//![12]

private:
    int m_stateCount;
    int m_lastIndex;
};

//![13]
QState *createGeometryState(QObject *w1, const QRect &rect1,
                            QObject *w2, const QRect &rect2,
                            QObject *w3, const QRect &rect3,
                            QObject *w4, const QRect &rect4,
                            QState *parent)
{
    QState *result = new QState(parent);
    result->assignProperty(w1, "geometry", rect1);
    result->assignProperty(w2, "geometry", rect2);
    result->assignProperty(w3, "geometry", rect3);
    result->assignProperty(w4, "geometry", rect4);

    return result;
}
//![13]


class GraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr)
        : QGraphicsView(scene, parent)
    {
    }

protected:
    void resizeEvent(QResizeEvent *event) override
    {
        fitInView(scene()->sceneRect());
        QGraphicsView::resizeEvent(event);
    }
};

class PuzzleWidget
/* class PuzzleWidget : QGraphicsScene */
{
	private:
		GraphicsView			window_;

		vector<QGraphicsRectWidget*>	tiles_;
		int				size_;
		int				numOfTiles_;


		QGraphicsScene	addButtons();
		void		setWindow(QGraphicsScene scene);
	public:
		PuzzleWidget(const int& size, QObject* paret=nullptr) :
			window_(0), tiles_(0), size_(size), numOfTiles_(size * size)
	{
		/* /1* 1 *1/ */
		/* /1* 2 *1/ */
		/* GraphicsView window(&addButtons()); */
		/* window.setFrameStyle(0); */
		/* window.setAlignment(Qt::AlignLeft | Qt::AlignTop); */
		/* window.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); */
		/* window.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); */
		/* /1* 3 *1/ */
		/*  QStateMachine machine; */
		/*  QState *group = new QState(); */
		/*  group->setObjectName("group"); */
		/*  QTimer timer; */
		/*  timer.setInterval(1250); */
		/*  timer.setSingleShot(true); */
		/*  QObject::connect(group, &QState::entered, &timer, QOverload<>::of(&QTimer::start)); */

		/*   machine.addState(group); */
		/*   machine.setInitialState(group); */
		/*   machine.start(); */
	}
};
#include "main.moc"
