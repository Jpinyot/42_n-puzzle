/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzleWidget.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpinyot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 11:20:42 by jpinyot           #+#    #+#             */
/*   Updated: 2020/10/05 11:51:41 by jpinyot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <QGraphicsScene>
#include <QGraphicsWidget>
#include <QPainter>
#include <QState>

using namespace std;

class QGraphicsRectWidget : public QGraphicsWidget
{
	public:
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *,
				QWidget *) override
		{
			painter->fillRect(rect(), Qt::blue);
		}
};

class PuzzleWidget : QGraphicsScene
{
	private:
		vector<QGraphicsRectWidget>	tiles_;
		int				size_;
		int				numOfTiles_;
	public:
		PuzzleWidget(const int& size, QObject* paret=nullptr) :
			QGraphicsScene(0, 0, 300, 300), tiles_(0), size_(size), numOfTiles_(size * size)
	{
		setBackgroundBrush(Qt::black);

		for (int i = 0; i < size_; i++) {
			QGraphicsRectWidget *button = new QGraphicsRectWidget;
			button->setZValue(i);
			addItem(button);
		}

		 QStateMachine machine;

		 QState *group = new QState();
		 group->setObjectName("group");
		 QTimer timer;
		 timer.setInterval(1250);
		 timer.setSingleShot(true);
		 QObject::connect(group, &QState::entered, &timer, QOverload<>::of(&QTimer::start));
	}
};
