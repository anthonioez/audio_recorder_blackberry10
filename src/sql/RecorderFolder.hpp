#ifndef RecorderFolder_HPP_
#define RecorderFolder_HPP_

#include <bb/data/SqlDataAccess>

#define recorder_folder_col_id		"_id"
#define recorder_folder_col_title	"title"
#define recorder_folder_col_desc	"desc"
#define recorder_folder_col_type	"type"
#define recorder_folder_col_flags	"flags"
#define recorder_folder_col_status	"status"
#define recorder_folder_col_stamp	"stamp"

using namespace bb::data;

class Q_CORE_EXPORT RecorderFolder: public QObject
{
	Q_OBJECT
	public:
		RecorderFolder(SqlDataAccess *sda);

		bool			copy(const QVariantMap &);

		int				getCount();
		bool	 		load();
		bool			load(const QString &sort, bool asc);

		bool			get(long id);
		bool			getByTitle(const QString &title);

		bool 			update();
		bool 			insert();
		bool			remove(long id);
		bool			clear();
		QVariantList 	getList();
		bool 			getLast();
		QString			getSortTable(int index);
	public:
		long 			id;

		QString			title;
		QString			desc;
		int				type;
		long			flags;
		int				status;
		long			stamp;

	private:
		QString			table;
		QVariantList	list;

		SqlDataAccess 	*sda;
};

#endif /* RecorderFolder_HPP_ */
