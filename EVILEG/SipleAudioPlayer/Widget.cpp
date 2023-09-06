#include "Widget.h"
#include "ui_Widget.h"
#include <QFileDialog>
#include <QDir>
#include <QToolButton>
#include <QTime>

Widget::Widget(QWidget *parent)	: QWidget(parent), ui(new Ui::Widget)
{
	ui->setupUi(this);

	m_playlist_model = new QStandardItemModel(this);
	ui->playlistView->setModel(m_playlist_model);
	m_playlist_model->setHorizontalHeaderLabels(QStringList() << tr("Audio track") << tr("File path"));

	ui->playlistView->hideColumn(1);
	ui->playlistView->verticalHeader()->setVisible(false);
	ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection);
	ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui->playlistView->horizontalHeader()->setStretchLastSection(true);

	m_player	= new QMediaPlayer(this);		//Init player
	m_playlist	= new QMediaPlaylist(m_player);
	m_player->setPlaylist(m_playlist);
	m_player->setVolume(70);
	m_playlist->setPlaybackMode(QMediaPlaylist::Loop);

	connect(ui->pushButtonAdd,  &QToolButton::clicked, this,		&Widget::on_btn_add_clicked);
	connect(ui->pushButtonPrev, &QToolButton::clicked, m_playlist,	&QMediaPlaylist::previous);
	connect(ui->pushButtonNext, &QToolButton::clicked, m_playlist,	&QMediaPlaylist::next);
	connect(ui->pushButtonPlay, &QToolButton::clicked, m_player,	&QMediaPlayer::play);
//	connect(ui->pushButtonPlay, &QToolButton::clicked, this,		&Widget::on_btn_play_clicked);
	connect(ui->pushButtonPause,&QToolButton::clicked, m_player,	&QMediaPlayer::pause);
	connect(ui->pushButtonStop, &QToolButton::clicked, m_player,	&QMediaPlayer::stop);

	connect(ui->playlistView,	&QTableView::doubleClicked,
			[this](const QModelIndex& index){m_playlist->setCurrentIndex(index.row());});

	connect(m_playlist, &QMediaPlaylist::currentIndexChanged,
			[this](int index){ui->labelCurrentTrack->setText(m_playlist_model->data(m_playlist_model->index(index, 0)).toString());});

	/*connect(m_player, &QMediaPlayer::position,
			[this]()
	{
		ui->sliderTrack->setValue(m_player->position());
		ui->sliderTrack->setMaximum(m_player->duration());
		QString duration = QString::number( ui->sliderTrack->maximum());
		ui->labelCurrentTrack->text().append(duration);
	}
	);*/

	connect(m_player, &QMediaPlayer::positionChanged, this, &Widget::on_position_changed);
	connect(m_player, &QMediaPlayer::durationChanged, this, &Widget::on_duration_changed);

}

Widget::~Widget()
{
	delete ui;
	delete m_playlist_model;
	delete m_playlist;
	delete m_player;
}

void Widget::on_btn_add_clicked()
{
	QStringList files = QFileDialog::getOpenFileNames(this, tr("Open files"), QString(), tr("Audio files (*.mp3 *.flac)"));
	for(QString filePath : files)
	{
		QList<QStandardItem*> items;
		items.append(new QStandardItem(QDir(filePath).dirName()));
		items.append(new QStandardItem(filePath));
		m_playlist_model->appendRow(items);
		m_playlist->addMedia(QUrl(filePath));
	}
}
void Widget::on_btn_play_clicked()
{
	//ui->sliderTrack->setValue(m_player->position());
	ui->sliderTrack->setMaximum(m_player->duration());
	QString duration = QString::number( ui->sliderTrack->maximum());
	//ui->labelCurrentTrack->setText(ui->labelCurrentTrack->text().append(duration));
	ui->labelDuration->setText(duration);
	m_player->play();
}

void Widget::on_sliderVolume_sliderMoved(int position)
{
	m_player->setVolume(position);
}

void Widget::on_sliderVolume_valueChanged(int value)
{
	m_player->setVolume(value);
	ui->labelVolume->setText(QString("Volume: ").append(QString::number(m_player->volume())));
}

void Widget::on_position_changed(qint64 value)
{
	ui->sliderTrack->setValue(value);
	QTime played = QTime::fromMSecsSinceStartOfDay(value);
	ui->labelPlayed->setText(QString("Played: ").append(played.toString("mm:ss")));
//	ui->labelPlayed->setText(QString("Played: ").append(QString::number(value)));
}

void Widget::on_duration_changed(qint64 position)
{
	ui->sliderTrack->setMaximum(position);
	QTime duration = QTime::fromMSecsSinceStartOfDay(position);
	ui->labelDuration->setText(duration.toString("mm:ss"));
}

void Widget::on_sliderTrack_valueChanged(qint64 position)
{
	m_player->setPosition(position);
}

void Widget::on_sliderTrack_sliderMoved(int position)
{
	m_player->setPosition(position);
}
