#pragma once

#include <QQuickItem>
#include <QTimer>
#include <aspire/export.hxx>
#include <deque>

namespace aspire
{
	class ASPIRE_EXPORT FrameMetrics : public QQuickItem
	{
		Q_OBJECT
		Q_PROPERTY(double fpsCurrent MEMBER fpsCurrent NOTIFY fpsCurrentChanged)
		Q_PROPERTY(double fpsMean MEMBER fpsMean NOTIFY fpsMeanChanged)
		Q_PROPERTY(double fpsRolling MEMBER fpsRolling NOTIFY fpsRollingChanged)
		Q_PROPERTY(double fpsMin MEMBER fpsMin NOTIFY fpsMinChanged)
		Q_PROPERTY(double fpsMax MEMBER fpsMax NOTIFY fpsMaxChanged)
		Q_PROPERTY(int rollingCount READ getRollingCount WRITE setRollingCount)
		Q_PROPERTY(int frameCount MEMBER frameCount NOTIFY frameCountChanged)
		Q_PROPERTY(Thread thread READ getThread WRITE setThread)
		Q_CLASSINFO("RegisterEnumClassesUnscoped", "false")
		QML_ELEMENT

	public:
		enum class Thread : int
		{
			Main,
			Render
		};
		Q_ENUM(Thread)

		static constexpr auto DefaultRollingCount{200};

		explicit FrameMetrics(QQuickItem* parent = nullptr);

		auto setRollingCount(int x) noexcept -> void;
		[[nodiscard]] auto getRollingCount() const noexcept -> int;

		auto setThread(Thread x) noexcept -> void;
		[[nodiscard]] auto getThread() const noexcept -> Thread;

		auto componentComplete() -> void override;
		auto updatePaintNode(QSGNode* /*unused*/, UpdatePaintNodeData* /*unused*/) -> QSGNode* override;

	signals:
		void fpsCurrentChanged(double);
		void fpsMeanChanged(double);
		void fpsRollingChanged(double);
		void fpsMinChanged(double);
		void fpsMaxChanged(double);
		void frameCountChanged(int);

	private:
		auto measure() -> void;

		std::deque<std::chrono::duration<double>> framesRolling;
		std::deque<std::chrono::duration<double>> frames;
		QTimer timer;
		std::chrono::steady_clock::time_point start{std::chrono::steady_clock::now()};
		double fpsCurrent{};
		double fpsRolling{};
		double fpsMean{};
		double fpsMin{std::numeric_limits<double>::max()};
		double fpsMax{};
		int frameCount{};
		int rollingCount{DefaultRollingCount};
		Thread thread{Thread::Main};
	};
}
