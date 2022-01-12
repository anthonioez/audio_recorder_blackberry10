#ifndef RecorderFile_HPP_
#define RecorderFile_HPP_

#include <bb/data/SqlDataAccess>

#define recorder_file_col_id			"_id"

#define recorder_file_col_folder		"folder"
#define recorder_file_col_title		"title"
#define recorder_file_col_desc			"desc"

#define recorder_file_col_path			"path"
#define recorder_file_col_duration		"duration"
#define recorder_file_col_size			"size"

#define recorder_file_col_flags		"flags"
#define recorder_file_col_status		"status"
#define recorder_file_col_stamp		"stamp"

using namespace bb::data;

class Q_CORE_EXPORT RecorderFile: public QObject
{
	Q_OBJECT
	public:
		RecorderFile(SqlDataAccess *sda);

		bool			copy(QVariantMap);

		int				getCount();
		int				getCountByFolder(long);
		bool	 		load();
		bool	 		load(const QString &sort, bool asc);
		bool	 		loadByFolder(long folder);
		bool	 		loadByFolder(long folder, const QString &sort, bool asc);

		bool	 		search(long fid, const QString &phrase, const QString &sort, bool asc);

		bool			get(long id);
		bool			getByPath(long id);

		int				getCount(long id);

		bool 			update();
		bool 			insert();
		bool			remove(long id);
		bool			removeByFolder(long id);
		bool			removeOnFolder();
		bool			clear();
		QVariantList 	getList();
		QString			getSortTable(int);
		bool			removeFile(const QString &path);
		int				removeFolderFiles(long id);

	public:
		long 			id;

		long 			folder;
		QString			title;
		QString			desc;

		QString			path;
		long			size;
		long			duration;

		long			flags;
		int				status;
		long			stamp;

	private:
		QString			table;
		QVariantList	list;

		SqlDataAccess 	*sda;
};

#endif /* RecorderFile_HPP_ */
