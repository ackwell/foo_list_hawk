
// Run the enclosed function in the main thread (lifted from zao's foo_wave_seekbar)
template <typename F>
void in_main_thread(F f) {
	struct in_main : main_thread_callback {
		void callback_run() override { f(); }
		in_main(F f) : f(f) {}
		F f;
	};
	static_api_ptr_t<main_thread_callback_manager>()->add_callback(new service_impl_t<in_main>(f));
}
