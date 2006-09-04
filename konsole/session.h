/*
    This file is part of Konsole, an X terminal.
    Copyright (C) 1997,1998 by Lars Doelle <lars.doelle@on-line.de>

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301  USA.
*/

#ifndef SESSION_H
#define SESSION_H

#include <kapplication.h>
#include <kmainwindow.h>
#include <QStringList>
#include <QByteArray>

#include "TEPty.h"
#include "TEWidget.h"
#include "TEmuVt102.h"


class KProcIO;
class KProcess;
class ZModemDialog;

class TESession : public QObject
{ Q_OBJECT

public:

  TESession(TEWidget* w,
            const QString &pgm, const QStringList & _args,
	    const QString &term, ulong winId, const QString &sessionId="session-1",
	    const QString &initial_cwd = QString());
  void changeWidget(TEWidget* w);
  TEWidget* widget() { return te; }
  ~TESession();

  /** 
   * Returns true if the session has created child processes which have not yet terminated 
   * This call may be expensive if there are a large number of processes running. 
   */
  bool        hasChildren();
  void        setConnect(bool r);  // calls setListenToKeyPress(r)
  void        setListenToKeyPress(bool l);
  TEmulation* getEmulation();      // to control emulation
  bool        isSecure();
  bool        isMonitorActivity();
  bool        isMonitorSilence();
  bool        isMasterMode();
  int schemaNo();
  int encodingNo();
  int fontNo();
  const QString& Term() const;
  const QString& SessionId() const;
  const QString& Title() const;
  const QString& IconName() const;
  const QString& IconText() const;

  /** 
   * Return the session title set by the user (ie. the program running in the terminal), or an
   * empty string if the user has not set a custom title
   */
  QString userTitle() const;
  /** 
   * Returns the title of the session for display in UI widgets (eg. window captions)
   */
  QString displayTitle() const;

  int keymapNo();
  QString keymap();
  QStringList getArgs();
  QString getPgm();
  QString getCwd();
  QString getInitial_cwd() { return initial_cwd; }
  void setInitial_cwd(const QString& _cwd) { initial_cwd=_cwd; }

  void setHistory(const HistoryType&);
  const HistoryType& history();

  void setMonitorActivity(bool);
  void setMonitorSilence(bool);
  void setMonitorSilenceSeconds(int seconds);
  void setMasterMode(bool);
  void setSchemaNo(int sn);
  void setEncodingNo(int index);
  void setKeymapNo(int kn);
  void setKeymap(const QString& _id);
  void setFontNo(int fn);
  void setTitle(const QString& _title);
  void setIconName(const QString& _iconName);
  void setIconText(const QString& _iconText);
  void setAddToUtmp(bool);
  void setXonXoff(bool);
  bool testAndSetStateIconName (const QString& newname);
  bool sendSignal(int signal);

  void setAutoClose(bool b) { autoClose = b; }

  // Additional functions for DCOP
  bool closeSession();
  void clearHistory();
  void feedSession(const QString &text);
  void sendSession(const QString &text);
  void renameSession(const QString &name);
  QString sessionName() { return title; }
  int sessionPID() { return sh->pid(); }
  void enableFullScripting(bool b);

  void startZModem(const QString &rz, const QString &dir, const QStringList &list);
  void cancelZModem();
  bool zmodemIsBusy() { return zmodemBusy; }

  void print(QPainter &paint, bool friendly, bool exact);

  QString schema();
  void setSchema(const QString &schema);
  QString encoding();
  void setEncoding(const QString &encoding);
  QString keytab();
  void setKeytab(const QString &keytab);
  QSize size();
  void setSize(QSize size);
  void setFont(const QString &font);
  QString font();

public Q_SLOTS:

  void run();
  void done();
  void done(int);
  void terminate();
  void setUserTitle( int, const QString &caption );
  void changeTabTextColor( int );
  void ptyError();
  void slotZModemDetected();
  void emitZModemDetected();

  void zmodemStatus(KProcess *, char *data, int len);
  void zmodemSendBlock(KProcess *, char *data, int len);
  void zmodemRcvBlock(const char *data, int len);
  void zmodemDone();
  void zmodemContinue();

Q_SIGNALS:

  void processExited();
  void receivedData( const QString& text );
  void done(TESession*);
  void updateTitle();
  void notifySessionState(TESession* session, int state);
  void changeTabTextColor( TESession*, int );

  void disableMasterModeConnections();
  void enableMasterModeConnections();
  void renameSession(TESession* ses, const QString &name);

  void openUrlRequest(const QString &cwd);

  void zmodemDetected(TESession *);
  void updateSessionConfig(TESession *);
  void resizeSession(TESession *session, QSize size);
  void setSessionEncoding(TESession *session, const QString &encoding);
  void getSessionSchema(TESession *session, QString &schema);
  void setSessionSchema(TESession *session, const QString &schema);

private Q_SLOTS:
  void onRcvBlock( const char* buf, int len );
  void monitorTimerDone();
  void notifySessionState(int state);
  void onContentSizeChange(int height, int width);
  void onFontMetricChange(int height, int width);

private:

  TEPty*         sh;
  TEWidget*      te;
  TEmulation*    em;

  bool           connected;
  bool           monitorActivity;
  bool           monitorSilence;
  bool           notifiedActivity;
  bool           masterMode;
  bool           autoClose;
  bool           wantedClose;
  QTimer*        monitorTimer;

  //FIXME: using the indices here
  // is propably very bad. We should
  // use a persistent reference instead.
  int            schema_no;
  int            font_no;
  int            silence_seconds;

  int            font_h;
  int            font_w;

  QString        title;
  QString        _userTitle;
  QString        iconName;
  QString        iconText; // as set by: echo -en '\033]1;IconText\007
  bool           add_to_utmp;
  bool           xon_xoff;
  bool           fullScripting;

  QString	 stateIconName;

  QString        pgm;
  QStringList       args;

  QString        term;
  ulong          winId;
  QString        sessionId;

  QString        cwd;
  QString        initial_cwd;

  // ZModem
  bool           zmodemBusy;
  KProcIO*       zmodemProc;
  ZModemDialog*  zmodemProgress;

  // Color/Font Changes by ESC Sequences

  QColor         modifiedBackground; // as set by: echo -en '\033]11;Color\007
  int            encoding_no;
};

#endif
