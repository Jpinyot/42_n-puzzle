/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzleWidget.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 11:20:42 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/05 16:09:31 by jpinyot          ###   ########.fr       */
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
#include <QtCore>
#include <QtWidgets>

const int k_tileSize = 50;
const int k_tilePosSeparation = 50;

using namespace std;


//![13]
/* QState *createGeometryState(QObject *w1, const QRect &rect1, */
/*                             QObject *w2, const QRect &rect2, */
/*                             QObject *w3, const QRect &rect3, */
/*                             QObject *w4, const QRect &rect4, */
/*                             QState *parent) */
/* { */
/*     QState *result = new QState(parent); */
/*     result->assignProperty(w1, "geometry", rect1); */
/*     result->assignProperty(w2, "geometry", rect2); */
/*     result->assignProperty(w3, "geometry", rect3); */
/*     result->assignProperty(w4, "geometry", rect4); */

/*     return result; */
/* } */
/* //![13] */

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
    /* Q_OBJECT */
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


class GraphicsView : public QGraphicsView
{
    /* Q_OBJECT */
public:
    GraphicsView(QGraphicsScene *scene, QWidget *parent = nullptr)
        : QGraphicsView(scene, parent)
    {
    }
    virtual ~GraphicsView() = default;

protected:
    void resizeEvent(QResizeEvent *event) override
    {
        fitInView(scene()->sceneRect());
        QGraphicsView::resizeEvent(event);
    }
};

class PuzzleWidget
{
	private:
		/* GraphicsView			window_; */

		vector<QGraphicsRectWidget*>	tiles_;
		int				size_;
		int				numOfTiles_;


		/* QGraphicsScene	addButtons(); */
		/* void		setWindow(QGraphicsScene scene); */
		QState *createGeometryState(QState *parent)
		{
			QState *result = new QState(parent);
			QRect rect(0, 0, 0, 0);
			for (int i = 0; i < tiles_.size(); i++) {
				result->assignProperty(tiles_[i], "geometry", rect);
				rect.moveLeft(rect.left() + k_tilePosSeparation);
				if ((i + 1) % size_ == 0) {
					rect.moveTo(0, rect.top() + k_tilePosSeparation);
				}
			}
			return result;
		}
	public:
		PuzzleWidget(const int& size, QObject* paret=nullptr) :
			tiles_(0), size_(size), numOfTiles_(size * size)
	{
    		QGraphicsScene scene(0, 0, 300, 300);
		scene.setBackgroundBrush(Qt::black);
		for (int i = 0; i < size_; i++) {
			QGraphicsRectWidget *tile = new QGraphicsRectWidget;
			tile->setZValue(i);
			tiles_.push_back(tile);
			scene.addItem(tile);
		}
   		GraphicsView window(&scene);
		window.setFrameStyle(0);
		window.setAlignment(Qt::AlignLeft | Qt::AlignTop);
		window.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		window.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

		QStateMachine machine;

		QState *group = new QState();
		group->setObjectName("group");
		QTimer timer;
		timer.setInterval(1250);
		timer.setSingleShot(true);
		QObject::connect(group, &QState::entered, &timer, QOverload<>::of(&QTimer::start));

		QState* state1 = createGeometryState(group); /* new createGeometryState() */


		QParallelAnimationGroup animationGroup;
		QSequentialAnimationGroup *subGroup;

		for (auto& tile : tiles_) {
			QPropertyAnimation *anim = new QPropertyAnimation(tile, "geometry");
			anim->setDuration(1000);
			anim->setEasingCurve(QEasingCurve::OutElastic);
			animationGroup.addAnimation(anim);

			subGroup = new QSequentialAnimationGroup(&animationGroup);
			subGroup->addAnimation(anim);
		}

			StateSwitcher *stateSwitcher = new StateSwitcher(&machine);
			stateSwitcher->setObjectName("stateSwitcher");
			group->addTransition(&timer, &QTimer::timeout, stateSwitcher);
			stateSwitcher->addState(state1, &animationGroup);
			/* stateSwitcher->addState(state2, &animationGroup); */
			/* //![7] */
			/* stateSwitcher->addState(state3, &animationGroup); */
			/* stateSwitcher->addState(state4, &animationGroup); */
			/* stateSwitcher->addState(state5, &animationGroup); */
			/* stateSwitcher->addState(state6, &animationGroup); */
			/* //![8] */
			/* stateSwitcher->addState(state7, &animationGroup); */
			//![8]

			//![9]
			machine.addState(group);
			machine.setInitialState(group);
			machine.start();
			//![9]

			window.resize(300, 300);
			window.show();

			/* return app.exec(); */
	}
};
#include "main.moc"
