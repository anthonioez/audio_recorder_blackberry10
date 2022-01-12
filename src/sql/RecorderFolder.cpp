#include "Recorder.hpp"
#include "RecorderFolder.hpp"
#include "utils.hpp"

RecorderFolder::RecorderFolder(SqlDataAccess *sda)
{
	table 	= "folders";
	id 		= 0;
	title 	= "";
	desc	= "";
	type	= 0;
	flags	= 0;
	stamp 	= 0;
	status 	= 0;

	this->sda = sda;
}

int	RecorderFolder::getCount()
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


bool RecorderFolder::copy(const QVariantMap &row)
{
	id 		= row[recorder_folder_col_id].toLongLong();
	title	= row[recorder_folder_col_title].toString();
	desc	= row[recorder_folder_col_desc].toString();
	type	= row[recorder_folder_col_type].toInt();
	flags	= row[recorder_folder_col_flags].toLongLong();
	status	= row[recorder_folder_col_status].toInt();
	stamp	= row[recorder_folder_col_stamp].toLongLong();

	return true;
}

QString	RecorderFolder::getSortTable(int index)
{
	switch(index)
	{
		case 0:
			return recorder_folder_col_title;
		case 1:
			return recorder_folder_col_desc;
		default:
			return recorder_folder_col_stamp;
	}
}


bool RecorderFolder::load()
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

bool RecorderFolder::load(const QString &sort, bool asc)
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

bool RecorderFolder::get(long id)
{
	QString query = "select * from " + table + " where " + recorder_folder_col_id + " = " + QString::number(id) + " LIMIT 1";

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

bool RecorderFolder::getByTitle(const QString &title)
{
	QVariantList getValues;
	getValues << title;

	QString query = "select * from " + table + " where " + recorder_folder_col_title + " = ? LIMIT 1";

	QVariant data = sda->execute(query, getValues);
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

bool RecorderFolder::insert()
{
	QVariantList insertValues;
	insertValues << title << desc << type << QString::number(flags) << QString::number(stamp) << status;

	sda->execute("insert into " + table + " ("
			+ recorder_folder_col_title	+ ", "
			+ recorder_folder_col_desc 	+ ", "
			+ recorder_folder_col_type	+ ", "
			+ recorder_folder_col_flags	+ ", "
			+ recorder_folder_col_stamp + ", "
			+ recorder_folder_col_status  + ") values (?, ?, ?, ?, ?, ?)", insertValues);

	if(!sda->hasError())
	{
		return true;
	}
	else
	{
		return false;
	}
}

//TODOSELECT LAST_INSERT_ROWID();

bool RecorderFolder::update()
{
	QVariantList updateValues;
	updateValues << title << desc << type << QString::number(flags) << QString::number(stamp) << status << QString::number(id);

	sda->execute("update " + table + " set "
			+ recorder_folder_col_title		+ " = ?, "
			+ recorder_folder_col_desc 		+ " = ?, "
			+ recorder_folder_col_type 	+ " = ?, "
			+ recorder_folder_col_flags 	+ " = ?, "
			+ recorder_folder_col_stamp 	+ " = ?, "
			+ recorder_folder_col_status 	+ " = ? where "
			+ recorder_folder_col_id + " = ?", updateValues);

	if(!sda->hasError())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool RecorderFolder::remove(long id)
{
	sda->execute("delete from " + table + " where " + QString(recorder_folder_col_id) + " = " + QString::number(id));
	if(!sda->hasError())
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool RecorderFolder::clear()
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

QVariantList RecorderFolder::getList()
{
	return list;
}

bool RecorderFolder::getLast()
{
	if(load())
	{
		if(list.size() > 0)
		{
			QVariantMap item = list.last().value<QVariantMap>();
			if(copy(item))
			{
				return true;
			}
		}
	}
	return false;
}
