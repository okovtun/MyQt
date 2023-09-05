#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
	Q_OBJECT

public:
	explicit Widget(QWidget *parent = nullptr);
	~Widget();

private slots:
	void on_btn_add_clicked();

private:
	Ui::Widget *ui;
	QStandardItemModel* m_playlist_model;
	QMediaPlayer*		m_player;
	QMediaPlaylist*		m_playlist;
};
#endif // WIDGET_H
