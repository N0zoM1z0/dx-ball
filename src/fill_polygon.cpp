#include "raster.h"
#include "raster_imports.h"
extern "C" {
#include "allocator.h"
}
#include <stdlib.h>
#include <string.h>

typedef struct RasterEdge {
    DxBallInt top, bottom, x;
    DxBallByte unknown[4];
    DxBallInt dx, dy, error;
} RasterEdge;

void DXBALL_RASTER_CALL dxball_fill_polygon(DxBallByte *pixels, DxBallInt pitch,
    const DxBallRasterPoint *points, DxBallInt count, DxBallByte color)
{
    RasterEdge *active_saved;
    DxBallRasterPoint b_point;
    DxBallRasterPoint first;
    DxBallInt pending_edge_count;
    DxBallInt previous_index;
    RasterEdge *edges;
    DxBallInt right;
    RasterEdge *edge_item;
    DxBallInt next;
    RasterEdge **pending;
    DxBallInt span_left;
    RasterEdge **active_list;
    DxBallByte *current_row_pixels;
    DxBallInt sort_stride;
    DxBallInt scanline_y;
    DxBallInt sort_current;
    DxBallInt live_edges_count;
    RasterEdge *pending_swap_edge;
    edges = (RasterEdge *)dxball_runtime_malloc((DxBallUInt)(count * sizeof(*edges)));
    pending = (RasterEdge **)dxball_runtime_malloc((DxBallUInt)(count * sizeof(*pending)));
    active_list = (RasterEdge **)dxball_runtime_malloc((DxBallUInt)(count * sizeof(*active_list)));
    if (edges == NULL || pending == NULL || active_list == NULL) {
        if (edges != NULL) dxball_heap_release(edges);
        if (pending != NULL) dxball_heap_release(pending);
        if (active_list != NULL) dxball_heap_release(active_list);
        return;
    }
    sort_current = 0;
    pending_edge_count = 0;
    for (; sort_current < count; ++sort_current) {
        first = points[sort_current];
        b_point = points[(sort_current + 1) % count];
        if (first.y == b_point.y)
            continue;
        if (first.y > b_point.y) {
            first = b_point;
            b_point = points[sort_current];
        }
        edges[pending_edge_count].top = first.y;
        edges[pending_edge_count].bottom = b_point.y;
        edges[pending_edge_count].x = first.x;
        edges[pending_edge_count].dx = b_point.x - first.x;
        edges[pending_edge_count].dy = b_point.y - first.y;
        edges[pending_edge_count].error = 0;
        pending[pending_edge_count] = &edges[pending_edge_count];
        ++pending_edge_count;
    }
    for (sort_stride = 1; sort_stride < pending_edge_count; sort_stride = sort_stride * 3 + 1) { }
    for (sort_stride /= 3; sort_stride > 0; sort_stride /= 3) {
        for (sort_current = sort_stride; sort_current < pending_edge_count; ++sort_current) {
            for (previous_index = sort_current - sort_stride; previous_index >= 0; previous_index -= sort_stride) {
                if (pending[previous_index + sort_stride]->top >= pending[previous_index]->top)
                    break;
                pending_swap_edge = pending[previous_index];
                pending[previous_index] = pending[previous_index + sort_stride];
                pending[previous_index + sort_stride] = pending_swap_edge;
            }
        }
    }
    live_edges_count = 0;
    next = 0;
    /* A nonhorizontal closed contour and representable arithmetic are the
       original routine's required domain; its zero-edge_item read is unresolved. */
    scanline_y = pending[next]->top;
    while (next < pending_edge_count || live_edges_count != 0) {
        while (next < pending_edge_count && pending[next]->top == scanline_y)
            active_list[live_edges_count++] = pending[next++];
        sort_current = 0;
        while (sort_current < live_edges_count) {
            if (active_list[sort_current]->bottom == scanline_y) {
                --live_edges_count;
                memmove(&active_list[sort_current], &active_list[sort_current + 1], (live_edges_count - sort_current) * sizeof(*active_list));
            } else {
                ++sort_current;
            }
        }
        for (sort_stride = 1; sort_stride < live_edges_count; sort_stride = sort_stride * 3 + 1) { }
        for (sort_stride /= 3; sort_stride > 0; sort_stride /= 3) {
            for (sort_current = sort_stride; sort_current < live_edges_count; ++sort_current) {
                for (previous_index = sort_current - sort_stride; previous_index >= 0; previous_index -= sort_stride) {
                    if (active_list[previous_index + sort_stride]->x >= active_list[previous_index]->x)
                        break;
                    active_saved = active_list[previous_index];
                    active_list[previous_index] = active_list[previous_index + sort_stride];
                    active_list[previous_index + sort_stride] = active_saved;
                }
            }
        }
        for (sort_current = 0; sort_current < live_edges_count; sort_current += 2) {
            span_left = active_list[sort_current]->x;
            right = active_list[sort_current + 1]->x;
            if (active_list[sort_current]->error > 0) ++span_left;
            if (active_list[sort_current + 1]->error <= 0) --right;
            if (span_left <= right) {
                current_row_pixels = pixels + scanline_y * pitch;
                dxball_fill_horizontal_span(current_row_pixels, span_left, right, color);
            }
        }
        for (sort_current = 0; sort_current < live_edges_count; ++sort_current) {
            edge_item = active_list[sort_current];
            edge_item->error += edge_item->dx;
            if (edge_item->dx < 0) {
                while (edge_item->dy <= -edge_item->error) {
                    edge_item->error += edge_item->dy;
                    --edge_item->x;
                }
            } else {
                while (edge_item->dy <= edge_item->error) {
                    edge_item->error -= edge_item->dy;
                    ++edge_item->x;
                }
            }
        }
        ++scanline_y;
    }
    dxball_heap_release(edges);
    dxball_heap_release(pending);
    dxball_heap_release(active_list);
    return;
}
