#ifndef RecorderFileList_HPP_
#define RecorderFileList_HPP_

#include <QObject>

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/Container>
#include <bb/cascades/ListView>
#include <bb/cascades/Page>
#include <bb/cascades/Label>
#include <bb/cascades/VisualNode>
#include <bb/cascades/ImageView>
#include <bb/cascades/ActionItem>
#include <bb/cascades/DeleteActionItem>
#include <bb/cascades/ActionBarPlacement>
#include <bb/cascades/MultiSelectHandler>

#include <bb/cascades/QListDataModel>

#include "sql/RecorderFile.hpp"
#include "sql/RecorderFolder.hpp"

using namespace bb::cascades;

class RecorderFileList: public QObject {
Q_OBJECT
public:
	RecorderFileList();
	virtual 	~RecorderFileList() {	}

	void		open(long);
	void		load();
	void		clear();
	void		setBB10(bool bb10);
	bool		removeFile(const QString &path);
	void		moveToFolder(long id, long folder);
	void		moveToDevice(long id, const QString &src);

private slots:
	void onChanged();

	void onMoveComplete(long, long);
	void onMoveCanceled();
	void onMoveChanged();

	void onOpenItem(QVariantList indexPath);
	void onPlayItem(QVariant indexPath);
	void onEditItem(QVariant indexPath);
	void onShareItem(QVariant indexPath);
	void onDeleteItem(QVariant indexPath);
	void onDeleteItems();

	void onFolderMoveItem(QVariant indexPath);
	void onDeviceMoveItem(QVariant indexPath);
	void onTouchClose(bb::cascades::TouchEvent* touchEvent);
	void onTouchClear(bb::cascades::TouchEvent* touchEvent);
	void onPopped(bb::cascades::Page *page);
	void onClear();
	void onSettingsChanged();

signals:
	void fileListClosed();
	void fileListChanged();

private:
	Page 			*mPage;
	Container		*mContainerTitle;
	Container		*mContainerNav;

	ActionItem		*mActionAction;
	DeleteActionItem		*mActionDelete;

	Label			*mLabelTitle;
	ListView 		*mListFiles;
	ImageView		*mImageTheme;
	ImageView		*mImageClear;
	ImageView		*mImageClose;

	QListDataModel<QVariant> 	*mDataModel;
	long			mFolder;
};

#endif /* RecorderFileList_HPP_ */
