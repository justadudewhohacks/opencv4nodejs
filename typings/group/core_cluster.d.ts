import { Mat } from "../Mat";
import { Vec2 } from "../Vec2";
import { Vec3 } from "../Vec3";
import { Vec4 } from "../Vec4";
import { Vec6 } from "../Vec6";
import { Point2 } from "../Point2";
import { Point3 } from "../Point3";
import { TermCriteria } from "../TermCriteria";


// double 	cv::kmeans (InputArray data, int K, InputOutputArray bestLabels, TermCriteria criteria, int attempts, int flags, OutputArray centers=noArray())
//  	Finds centers of clusters and groups input samples around the clusters. More...
//  
//  	Splits an element set into equivalency classes. More...
export function kmeans(data: Point2[], k: number, termCriteria: TermCriteria, attempts: number, flags: number): { labels: number[], centers: Point2[] };
export function kmeans(data: Point3[], k: number, termCriteria: TermCriteria, attempts: number, flags: number): { labels: number[], centers: Point3[] };

// template<typename _Tp , class _EqPredicate >
// int 	partition (const std::vector< _Tp > &_vec, std::vector< int > &labels, _EqPredicate predicate=_EqPredicate())
export function partition(data: Point2[], predicate: (pt1: Point2, pt2: Point2) => boolean): { labels: number[], numLabels: number };
export function partition(data: Point3[], predicate: (pt1: Point3, pt2: Point3) => boolean): { labels: number[], numLabels: number };
export function partition(data: Vec2[], predicate: (vec1: Vec2, vec2: Vec2) => boolean): { labels: number[], numLabels: number };
export function partition(data: Vec3[], predicate: (vec1: Vec3, vec2: Vec3) => boolean): { labels: number[], numLabels: number };
export function partition(data: Vec4[], predicate: (vec1: Vec4, vec2: Vec4) => boolean): { labels: number[], numLabels: number };
export function partition(data: Vec6[], predicate: (vec1: Vec6, vec2: Vec6) => boolean): { labels: number[], numLabels: number };
export function partition(data: Mat[], predicate: (mat1: Mat, mat2: Mat) => boolean): { labels: number[], numLabels: number };
