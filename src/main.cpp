#include "Recorder.hpp"
#include "utils.hpp"

void myMessageOutput(QtMsgType type, const char* msg)
{
	Q_UNUSED(type)

	fprintf(stderr, "%s\n", msg);
}

Q_DECL_EXPORT int main(int argc, char **argv)
{
	Application app(argc, argv);

	qInstallMsgHandler(myMessageOutput);

	QTranslator translator;
	QString locale_string = QLocale().name();
	QString filename = QString("RecorderPlus_%1").arg(locale_string);
	if (translator.load(filename, "app/native/qm"))
	{
		app.installTranslator(&translator);
	}

	recorder = new Recorder(&app);
	recorder->startApp();

	return Application::exec();
}

