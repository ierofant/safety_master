#include <boost/bind.hpp>
#include "master.hpp"

using namespace boost::asio;

storage::storage(master &service)
	: service(service),
	  timer(service)
{

}

void
storage::start()
{
	timer.expires_from_now(boost::chrono::milliseconds(500));
	timer.async_wait(boost::bind(&storage::on_timeout, this, placeholders::error));
}

void
storage::on_timeout(const boost::system::error_code &error)
{
	if(error != boost::asio::error::operation_aborted)
	{
		service.refresh_vartable();
		start();
	}
}