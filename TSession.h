#ifndef TSESSION_HPP
#define TSESSION_HPP

struct TSession
{
  wxString m_host;
  wxString m_port;
  wxString m_user;
  wxString m_pass;
  wxString m_prot;

  // FTPS
  NPL::TLS m_ccTls;
  NPL::TLS m_dcTls;

  // SSH

  virtual void StartSession() {};
  virtual void StopSession() {};
};

#endif