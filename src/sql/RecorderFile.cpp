#include "Recorder.hpp"
#include "RecorderFile.hpp"
#include "utils.hpp"

RecorderFile::RecorderFile(SqlDataAccess *sda)
{
	table 		= "files";
	id 			= 0;

	folder		= 0;
	title 		= "";
	desc 		= "";

	size		= 0;
	duration	= 0;
	size		= 0;

	flags	= 0;
	stamp 	= 0;
	status 	= 0;

	this->sda = sda;
}

bool RecorderFile::copy(QVariantMap row)
{
	id 			= row[recorder_file_col_id].toLongLong();
	folder		= row[recorder_file_col_folder].toLongLong();
	title		= row[recorder_file_col_title].toString();
	desc		= row[recorder_file_col_desc].toString();

	path		= row[recorder_file_col_path].toString();
	size		= row[recorder_file_col_size].toLongLong();
	duration	= row[recorder_file_col_duration].toLongLong();

	flags		= row[recorder_file_col_flags].toLongLong();
	status		= row[recorder_file_col_status].toInt();
	stamp		= row[recorder_file_col_stamp].toLongLong();

	return true;
}

bool RecorderFile::load()
{
	QString query = "select * from " + table + " where 1 order by _id desc";

	QVariant data = sda->execute(query);
	if(!sda->hasError())
	{
		list = data.value<QVariantList>();
		return true;
	}
	return false;
}

bool RecorderFile::load(const QString &sort, bool asc)
{
	QString query = "select * from " + table + " where 1 order by " + sort + " " + (asc ? "asc" : "desc");

	QVariant data = sda->execute(query);
	if(!sda->hasError())
	{
		list = data.value<QVariantList>();
		return true;
	}
	return false;
}

bool RecorderFile::loadByFolder(long folder)
{
	QString query = "select * from " + table + " where " + recorder_file_col_folder + " = " + QString::number(folder) + " order by _id desc";

	QVariant data = sda->execute(query);
	if(!sda->hasError())
	{
		list = data.value<QVariantList>();
		return true;
	}
	return false;
}


bool RecorderFile::loadByFolder(long fid, const QString &sort, bool asc)
{
	QString fs = "1";

	if(fid != 0) fs = QString("%1 = %2").arg(recorder_file_col_folder).arg(fid);

	QString query = "select * from " + table + " where " + fs + " order by " + sort + " " + (asc ? "asc" : "desc");

//	qDebug() << "query: " << query;

	QVariant data = sda->execute(query);
	if(!sda->hasError())
	{
		list = data.value<QVariantList>();
		return true;
	}
	return false;
}

bool RecorderFile::search(long folder, const QString &phrase, const QString &sort, bool asc)
{
	if(phrase.trimmed().isEmpty())
	{
		return false;
	}

	QString fquery = "";
	if(folder > 0)
	{
		fquery += recorder_file_col_folder + QString(" = ") + QString::number(folder);
		fquery += QString(" AND ");
	}

	QString lquery = "";
	QStringList slist = phrase.split(" ");

	for(int i = 0; i < slist.size(); i++)
	{
		QString phr = slist.at(i);

		if(!lquery.isEmpty())
		{
			lquery += QString(" OR ");
		}
		lquery += QString("(");
		lquery += recorder_file_col_title + QString(" LIKE '%") + phr + QString("%'");
		lquery += QString(" OR ");
		lquery += recorder_file_col_desc + QString(" LIKE '%") + phr + QString("%'");
		lquery += QString(")");
	}

	QString squery = "";
	squery += fquery;
	squery += QString("(");
	squery += lquery;
	squery += QString(")");

	QString query = "select * from " + table + " where " + squery + " order by " + sort + " " + (asc ? "asc" : "desc");

	QVariant data = sda->execute(query);
	if(!sda->hasError())
	{
		list = data.value<QVariantList>();
		return true;
	}
	return false;
}

bool RecorderFile::get(long id)
{
	QString query = "select * from " + table + " where " + recorder_file_col_id + " = " + QString::number(id) + " LIMIT 1";

	QVariant data = sda->execute(query);
	if(!sda->hasError())
	{
		QVariantList list = data.value<QVariantList>();

		if(list.size() > 0)
		{
			QVariantMap row = list.at(0).value<QVariantMap>();
			if(copy(row))
			{
				return true;
			}
		}
	}
	return false;
}

bool RecorderFile::insert()
{
	QVariantList insertValues;
	insertValues << QString::number(folder) << title << desc
			<< path << QString::number(duration) << QString::number(size)
			<< QString::number(flags) << QString::number(stamp) << status;

	sda->execute("insert into " + table + " ("
			+ recorder_file_col_folder	+ ", "
			+ recorder_file_col_title	+ ", "
			+ recorder_file_col_desc 	+ ", "

			+ recorder_file_col_path	+ ", "
			+ recorder_file_col_duration 	+ ", "
			+ recorder_file_col_size 	+ ", "

			+ recorder_file_col_flags	+ ", "
			+ recorder_file_col_stamp 	+ ", "
			+ recorder_file_col_status  + ") values (?, ?, ?,  ?, ?, ?,  ?, ?, ?)", insertValues);

	if(!sda->hasError())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool RecorderFile::update()
{
	QVariantList updateValues;
	updateValues << QString::number(folder) << title << desc
			<< path << QString::number(duration) << QString::number(size)
			<< QString::number(flags) << QString::number(stamp) << status
			<< QString::number(id);

	sda->execute("update " + table + " set "
			+ recorder_file_col_folder		+ " = ?, "
			+ recorder_file_col_title		+ " = ?, "
			+ recorder_file_col_desc 		+ " = ?, "

			+ recorder_file_col_path 		+ " = ?, "
			+ recorder_file_col_duration	+ " = ?, "
			+ recorder_file_col_size 		+ " = ?, "

			+ recorder_file_col_flags 		+ " = ?, "
			+ recorder_file_col_stamp 		+ " = ?, "
			+ recorder_file_col_status 	+ " = ? where "
			+ recorder_file_col_id + " = ?", updateValues);

	if(!sda->hasError())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool RecorderFile::remove(long id)
{
	sda->execute("delete from " + table + " where " + QString(recorder_file_col_id) + " = " + QString::number(id));
	if(!sda->hasError())
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool RecorderFile::removeByFolder(long folder)
{
	sda->execute("delete from " + table + " where " + QString(recorder_file_col_folder) + " = " + QString::number(folder));
	if(!sda->hasError())
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool RecorderFile::removeOnFolder()
{
	sda->execute("delete from " + table + " where " + QString(recorder_file_col_folder) + " > 0");
	if(!sda->hasError())
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool RecorderFile::clear()
{
	sda->execute("delete from " + table + " where 1");
	if(!sda->hasError())
	{
		return true;
	}
	else
	{
		return false;
	}
}

QVariantList RecorderFile::getList()
{
	return list;
}

int	RecorderFile::getCount()
{
	int count = 0;
	QString query = "select count(*) as total from " + table + " where 1";
	QVariant data = sda->execute(query);
	if(!sda->hasError())
	{
		QVariantList list = data.value<QVariantList>();

		if(list.size() > 0)
		{
			QVariantMap map = list.at(0).value<QVariantMap>();
			count = map["total"].toInt();
			return count;
		}
	}
	return count;
}

int	RecorderFile::getCountByFolder(long folder)
{
	int count = 0;
	QString query = "select count(*) as total from " + table + " where " + QString(recorder_file_col_folder) + " = " + QString::number(folder);
	QVariant data = sda->execute(query);
	if(!sda->hasError())
	{
		QVariantList list = data.value<QVariantList>();

		if(list.size() > 0)
		{
			QVariantMap map = list.at(0).value<QVariantMap>();
			count = map["total"].toInt();
			return count;
		}
	}
	return count;
}

QString	RecorderFile::getSortTable(int index)
{
	switch(index)
	{
		case 0:
			return recorder_file_col_title;
		case 1:
			return recorder_file_col_desc;
		case 2:
			return recorder_file_col_duration;
		case 3:
			return recorder_file_col_size;
		case 4:
			return recorder_file_col_stamp;
		case 5:
			return recorder_file_col_id;
		default:
			return recorder_file_col_folder;
	}
}

int RecorderFile::removeFolderFiles(long id)
{
	int count = 0;
	RecorderFile *data = new RecorderFile(recorder->mSda);
	if(data->loadByFolder(id))
	{
		QVariantList list = data->getList();

		for(int i = 0; i < list.size(); i++)
		{
			QVariantMap map = list.at(i).value<QVariantMap>();

			RecorderFile *item = new RecorderFile(recorder->mSda);
			if(item->copy(map))
			{
				if(item->remove(item->id))
				{
					item->removeFile(item->path);
					count++;
				}
			}
		}
	}
	return count;
}

bool RecorderFile::removeFile(const QString &path)
{
	QFile file(path);
	if(file.exists())
	{
		if(file.remove())
		{
			return true;
		}
	}

	return false;
}
