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
	void on_btn_play_clicked();

	void on_sliderVolume_sliderMoved(int position);
	void on_sliderVolume_valueChanged(int value);


	void on_position_changed(qint64 value);
	void on_duration_changed(qint64 position);

	void on_sliderTrack_valueChanged(qint64 position);
	void on_sliderTrack_sliderMoved(int position);

private:
	Ui::Widget *ui;
	QStandardItemModel* m_playlist_model;
	QMediaPlayer*		m_player;
	QMediaPlaylist*		m_playlist;
};
#endif // WIDGET_H
