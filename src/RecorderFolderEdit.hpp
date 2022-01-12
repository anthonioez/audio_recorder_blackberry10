#ifndef RecorderFolderEdit_HPP_
#define RecorderFolderEdit_HPP_

#include <QObject>

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/NavigationPane>
#include <bb/cascades/ListView>
#include <bb/cascades/Page>
#include <bb/cascades/Label>
#include <bb/cascades/TextField>
#include <bb/cascades/TextArea>
#include <bb/cascades/AbstractTextControl>
#include <bb/cascades/Sheet>
#include <bb/cascades/ImageView>
#include <bb/cascades/ActionItem>
#include <bb/cascades/ActionBarPlacement>


#include "sql/RecorderFolder.hpp"

using namespace bb::cascades;

class RecorderFolderEdit: public QObject {
Q_OBJECT
public:
	RecorderFolderEdit();
	virtual 	~RecorderFolderEdit() {	}
	void		add();
	void		open(long id);
	void 		start();
	void		save();
	void		remove();
	void		close();

	void		setBB10(bool);
	void		pushed();
	void		popped();
private slots:
	void onSave();
	void onDelete();
	void onClose();

	void onSubmitted(bb::cascades::AbstractTextControl *submitter);
	void onTextChanging(const QString);
	void onTouchSave(bb::cascades::TouchEvent* touchEvent);
	void onTouchRemove(bb::cascades::TouchEvent* touchEvent);
	void onTouchClose(bb::cascades::TouchEvent* touchEvent);

	void onPushed(bb::cascades::Page *page);
	void onPopped(bb::cascades::Page *page);

	void onSettingsChanged();

signals:
	void folderChanged();
	void folderEditClosed();

private:
	Sheet			*mSheet;
	Page 			*mPage;

	Container		*mContainerTitle;
	Container		*mContainerNav;

	Label			*mLabelTitle;
	TextField		*mTextTitle;
	TextArea		*mTextDesc;
	ImageView		*mImageTheme;

	ImageView		*mImageSave;
	ImageView		*mImageDelete;
	ImageView		*mImageUndo;
	ImageView		*mImageRedo;
	ImageView		*mImageClose;

	RecorderFolder	*mFolder;

	int				mUndoIndex;
	QStringList		mUndoList;

	long			mId;
};

#endif /* RecorderFolderEdit_HPP_ */
