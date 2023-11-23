#include "src/hooking/hooking.h"
#include "src/memory/Pointers/Pointers.h"
namespace Base {
	bool hooks::send_http_request(CHttpRequest* request) {
		//LOG(Info, "\nSet {}://{}{}\nRequest: \n{}, Response: \n{}", request->m_scheme, request->m_host, request->m_path, request->m_request_headers ? request->m_request_headers : "", request->m_response_headers ? request->m_response_headers : "");
		if (request->m_request_data && request->m_request_data->m_data) {
			const auto path{ std::string(request->m_path) };
			for (auto blocked_apis : { "SubmitCompressed", "SubmitRealTime", "Bonus" }) {
				if (path.find(blocked_apis) != std::string::npos) {
					strcpy(request->m_host, "amazon.com");
					RET_CALL_DECL(send_http_request, request);
				}
			}
		}
		RET_CALL_DECL(send_http_request, request);
	}
}