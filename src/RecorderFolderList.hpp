#ifndef RecorderFolderList_HPP_
#define RecorderFolderList_HPP_

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
#include <bb/cascades/ActionBarPlacement>
#include <bb/cascades/MultiSelectHandler>

#include <bb/cascades/QListDataModel>

#include "sql/RecorderFile.hpp"
#include "sql/RecorderFolder.hpp"

using namespace bb::cascades;

class RecorderFolderList: public QObject {
Q_OBJECT
public:
	RecorderFolderList();
	virtual 	~RecorderFolderList() {	}

	void		open();
	void		load();
	void		add();
	void		updateList();
	void		setBB10(bool bb10);
	int			removeFolderFiles(long);

private slots:
	void onChanged();
	void onEditClosed();
	void onOpen(QVariantList indexPath);

	void onOpenItem(QVariant indexPath);
	void onEditItem(QVariant indexPath);
	void onDefaultItem(QVariant indexPath);
	void onDeleteItem(QVariant indexPath);
	void onDeleteItems();

	void onTouchAdd(bb::cascades::TouchEvent* touchEvent);
	void onTouchClose(bb::cascades::TouchEvent* touchEvent);

	void onAdd();
	void onSettingsChanged();

signals:

private:
	Page 			*mPage;
	Container		*mContainerTitle;
	Container		*mContainerNav;

	Label			*mLabelTitle;
	ListView 		*mListFolders;
	ImageView		*mImageTheme;
	ImageView		*mImageAdd;
	ImageView		*mImageClose;

	QListDataModel<QVariant> 	*mDataModel;
};

#endif /* RecorderFolderList_HPP_ */
