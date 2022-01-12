#ifndef RecorderFolderSelector_HPP_
#define RecorderFolderSelector_HPP_

#include <QObject>

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/ListView>
#include <bb/cascades/Page>
#include <bb/cascades/Label>
#include <bb/cascades/ImageView>
#include <bb/cascades/ActionItem>
#include <bb/cascades/ActionBarPlacement>

#include <bb/cascades/QListDataModel>

#include "sql/RecorderFolder.hpp"

using namespace bb::cascades;

class RecorderFolderSelector: public QObject {
Q_OBJECT
public:
	RecorderFolderSelector();
	virtual 	~RecorderFolderSelector() {	}
	void		open(long, long);
	void		close();
	void		cancel();

	void		setBB10(bool);
	void		load();
	void		addFolder();

private slots:
	void onSelect(QVariantList indexPath);
	void onSelectItem(QVariant index);

	void onCancel();
	void onAdd();
	void onSettingsChanged();
	void onTouchAdd(bb::cascades::TouchEvent* touchEvent);
	void onTouchCancel(bb::cascades::TouchEvent* touchEvent);

	void onFolderChanged();
	void onFolderEditClosed();

signals:
	void folderSelected(long, long);
	void folderCanceled();
	void folderChanged();

private:
	Page			*mPage;

	Container		*mContainerTitle;
	Container		*mContainerNav;

	Label			*mLabelTitle;
	ListView 		*mListFolders;
	ImageView		*mImageTheme;

	ImageView		*mImageAdd;
	ImageView		*mImageCancel;

	QVariantList 				mList;
	QListDataModel<QVariant> 	*mDataModel;

	long			mId;
	long			mFolder;
};

#endif /* RecorderFolderSelector_HPP_ */
