#include <aspire/FrameMetrics.h>

using aspire::FrameMetrics;

FrameMetrics::FrameMetrics(QQuickItem* parent) : QQuickItem{parent}
{
	this->setFlag(QQuickItem::Flag::ItemHasContents);

	QObject::connect(&this->timer, &QTimer::timeout, this, [this] { this->measure(); });
}

auto FrameMetrics::setRollingCount(int x) noexcept -> void
{
	this->rollingCount = x;
}

auto FrameMetrics::getRollingCount() const noexcept -> int
{
	return this->rollingCount;
}

auto FrameMetrics::setThread(Thread x) noexcept -> void
{
	this->thread = x;
}

auto FrameMetrics::getThread() const noexcept -> Thread
{
	return this->thread;
}

auto FrameMetrics::componentComplete() -> void
{
	this->QQuickItem::componentComplete();

	switch(this->thread)
	{
		case Thread::Main:
			this->timer.start();
			break;

		case Thread::Render:
			this->setFlag(QQuickItem::Flag::ItemHasContents);
			break;

		default:
			break;
	}
}

auto FrameMetrics::updatePaintNode(QSGNode* /*unused*/, UpdatePaintNodeData* /*unused*/) -> QSGNode*
{
	this->update();
	this->measure();

	return nullptr;
}

auto FrameMetrics::measure() -> void
{
	const auto now = std::chrono::steady_clock::now();
	const auto elapsed = std::chrono::duration<double>(now - this->start);
	this->frames.emplace_back(elapsed);
	this->framesRolling.emplace_back(elapsed);

	while(static_cast<int>(this->framesRolling.size()) >= this->rollingCount)
	{
		this->framesRolling.pop_front();
	}

	this->fpsCurrent = 1.0 / elapsed.count();
	this->fpsMin = std::min(this->fpsMin, this->fpsCurrent);
	this->fpsMax = std::max(this->fpsMax, this->fpsCurrent);
	auto sum = std::accumulate(std::begin(this->framesRolling), std::end(this->framesRolling), std::chrono::duration<double>::zero());
	this->fpsRolling = 1.0 / (sum.count() / static_cast<double>(this->framesRolling.size()));

	sum = std::accumulate(std::begin(this->frames), std::end(this->frames), std::chrono::duration<double>::zero());
	this->fpsMean = 1.0 / (sum.count() / static_cast<double>(this->frames.size()));
	this->frameCount = static_cast<int>(this->frames.size());

	this->fpsCurrentChanged(this->fpsCurrent);
	this->fpsMinChanged(this->fpsMin);
	this->fpsMaxChanged(this->fpsMax);
	this->fpsRollingChanged(this->fpsRolling);
	this->fpsMeanChanged(this->fpsMean);
	this->frameCountChanged(this->frameCount);

	this->start = now;
}